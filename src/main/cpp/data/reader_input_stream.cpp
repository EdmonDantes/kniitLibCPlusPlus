/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include "algorithm"
#include "data/reader_input_stream.h"

KNIIT_LIB_NAMESPACE {

    Number ReaderInputStream::read() {
        if (!stream->canRead()) {
            throw createException2("ReaderInputStream", "Can not read stream");
        }

        prevPosition = stream->position();
        return codec->decodeOne(stream, byteOrder);
    }

    void ReaderInputStream::unread() {
        stream->position(prevPosition);
    }

    void ReaderInputStream::init(InputStream<uint8>* stream, const Codec* codec, ByteOrder byteOrder) {
        this->stream = stream;
        this->codec = codec;
        this->byteOrder = byteOrder;
    }

    Number ReaderInputStream::hexCharToValue(uintmax startPosition, Number ch) {
        uint8 tmp = ch.getUInt8();
        if (ch >= '0' && ch <= '9') {
            tmp -= '0';
        } else if (ch >= 'a' && ch <= 'f') {
            tmp -= 'a' - 10;
        } else if (ch >= 'A' && ch <= 'F') {
            tmp -= 'A' - 10;
        } else {
            stream->position(startPosition);
            createException2("ReaderInputStream", "Wrong color format");
        }
        return tmp;
    }

    ReaderInputStream::ReaderInputStream(InputStream<uint8>* stream, const Codec* codec, ByteOrder byteOrder) {
        init(stream, codec, byteOrder);
    }

    bool ReaderInputStream::canRead() {
        return this->stream->canRead() && codec != nullptr;
    }

    Number ReaderInputStream::readChar() {
        return read();
    }

    String ReaderInputStream::readString(uintmax length, const DelimiterStrategy& delimiterStrategy, bool addLastChar) {
        String result;
        while (result.size() < length || length < 1) {
            Number ch = readChar();
            if (delimiterStrategy.hasDelimiter(ch)) {
                if (!delimiterStrategy.isSkipDelimiters()) {
                    unread();
                }
                if (addLastChar) {
                    result += ch;
                }
                break;
            }

            result += ch;
        }

        return std::move(result);
    }

    bool ReaderInputStream::readBoolean() {
        uintmax startPosition = stream->position();

        String word;
        while (canRead() && word.size() < 5) {

            if (word == "true") {
                return true;
            }

            Number ch = readChar();

            int lowerCh = tolower(ch.getInt());
            if (word.size() < 1) {
                if (ch == '1' || ch == '0') {
                    return ch == '1';
                } else if (ch >= '0' && ch <= '9' || lowerCh <= 'a' || lowerCh >= 'z') {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong format");
                } else {
                    word += Number(lowerCh);
                }
            } else {
                if (lowerCh >= 'a' && lowerCh <= 'z') {
                    word += Number(lowerCh);
                } else {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong format");
                }
            }
        }

        if (word == "true") {
            return true;
        } else if (word == "false") {
            return false;
        } else {
            stream->position(startPosition);
            throw createException2("ReaderInputStream", "Wrong format");
        }
    }


    Number ReaderInputStream::readNumber(const DelimiterStrategy& delimiterStrategy, bool throwOnUnknownChar) {
        uintmax startPosition = stream->position();

        int decimalPartShift = -1;
        bool sign = false;

        union _number {
            uintmax integer;
            double decimal;
        };

        _number number{};

        number.integer = 0;

        while (canRead()) {
            Number ch = readChar();

            if (ch >= '0' && ch <= '9') {
                if (decimalPartShift > -1) {
                    double decimalPart = ch.getInt() - '0';
                    for (int i = decimalPartShift++; i > -1; i--) {
                        decimalPart /= 10;
                    }
                    number.decimal += decimalPart;
                } else {
                    number.integer *= 10;
                    number.integer += ch.getUInt() - '0';
                }
            } else if ((ch == ',' || ch == '.') && decimalPartShift < 0) {
                decimalPartShift = 0;
                number.decimal = number.integer;
            } else if (ch == '-' && (stream->position() - startPosition) < 2) {
                sign = true;
            } else if (delimiterStrategy.hasDelimiter(ch)) {
                if (!delimiterStrategy.isSkipDelimiters()) {
                    unread();
                }
                break;
            } else if (throwOnUnknownChar) {
                stream->position(startPosition);
                throw createException2("ReaderInputStream", "Wrong number format");
            } else {
                unread();
                break;
            }
        }

        Number result = decimalPartShift > -1 ? Number(number.decimal) : Number(number.integer);
        return sign ? -result : result;
    }

    Number ReaderInputStream::readColor(const DelimiterStrategy& delimiterStrategy) {
        uintmax startPosition = stream->position();

        int8 countCharacterInSharpType = -1;
        uint8 args[8];
        String word;

        while (canRead()) {
            Number ch = readChar();

            if (ch == '#') {
                if (word.isEmpty()) {
                    countCharacterInSharpType = 0;
                    continue;
                } else {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong color format");
                }
            }

            if (countCharacterInSharpType > -1) {
                if (delimiterStrategy.hasDelimiter(ch)) {
                    if (!delimiterStrategy.isSkipDelimiters()) {
                        unread();
                    }
                    break;
                }
                args[countCharacterInSharpType] = hexCharToValue(startPosition, ch).getUInt8();
                countCharacterInSharpType++;
            } else {
                if (ch == '(') {
                    word = word.toLower();
                    Number betweenNumber[1] {';'};
                    Number lastNumber[1] {')'};
                    DelimiterStrategy betweenNumberStrategy(betweenNumber, 1, true);
                    DelimiterStrategy lastNumberStrategy(lastNumber, 1, true);
                    if (word == "rgb") {
                        try {
                            Number r = readNumber(betweenNumberStrategy);
                            Number g = readNumber(betweenNumberStrategy);
                            Number b = readNumber(lastNumberStrategy);

                            if (r.isDouble() || g.isDouble() || b.isDouble()) {
                                r *= 255;
                                g *= 255;
                                b *= 255;
                            }

                            return ((r.getUInt() & 0xff) << 16) + ((g.getUInt() & 0xff) << 8) + (b.getUInt() & 0xff);
                        }
                        catch (Exception& e) {
                            stream->position(startPosition);
                            throw createException3("ReaderInputStream",
                                "Can not parse numbers",
                                new Exception(std::move(e)));
                        }
                    } else if (word == "argb") {
                        try {
                            Number a = readNumber(betweenNumberStrategy);
                            Number r = readNumber(betweenNumberStrategy);
                            Number g = readNumber(betweenNumberStrategy);
                            Number b = readNumber(lastNumberStrategy);

                            if (a.isDouble() || r.isDouble() || g.isDouble() || b.isDouble()) {
                                a *= 255;
                                r *= 255;
                                g *= 255;
                                b *= 255;
                            }

                            return ((a.getUInt() & 0xff) << 24) + ((r.getUInt() & 0xff) << 16) + ((g.getUInt() & 0xff)
                                << 8) + (b.getUInt() & 0xff);
                        }
                        catch (Exception& e) {
                            stream->position(startPosition);
                            throw createException3("ReaderInputStream",
                                "Can not parse numbers",
                                new Exception(std::move(e)));
                        }
                    } else {
                        stream->position(startPosition);
                        throw createException2("ReaderInputStream", "Wrong color format");
                    }
                } else {
                    word += ch;
                }


                if (word.size() > 4) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong color format");
                }
            }
        }

        if (countCharacterInSharpType > -1) {
            uint32 result = 0;
            if (countCharacterInSharpType == 8) {
                for (int i = 0; i < 4; ++i) {
                    uint8 tmp = (args[i * 2] << 4) + args[i * 2 + 1];
                    result += ((uintmax)tmp) << (24 - 8 * i);
                }
            } else if (countCharacterInSharpType == 6) {
                for (int i = 0; i < 3; ++i) {
                    uint8 tmp = (args[i * 2] << 4) + args[i * 2 + 1];
                    result += ((uintmax)tmp) << (16 - 8 * i);
                }
            } else if (countCharacterInSharpType == 4) {
                for (int i = 0; i < 4; ++i) {
                    uint8 tmp = 0xff * ((float) args[i] / (float)0xf);
                    result += ((uintmax)tmp) << (24 - 8 * i);
                }
            } else if (countCharacterInSharpType == 3) {
                for (int i = 0; i < 3; ++i) {
                    uint8 tmp = 0xff * ((float) args[i] / (float)0xf);
                    result += ((uintmax)tmp) << (16 - 8 * i);
                }
            } else {
                stream->position(startPosition);
                throw createException2("ReaderInputStream", "Wrong color format");
            }
            return result;
        }

        stream->position(startPosition);
        throw createException2("ReaderInputStream", "Wrong color format");
    }

    List<uint8> ReaderInputStream::readHex(uintmax length, const DelimiterStrategy& delimiterStrategy) {
        uintmax startPosition = stream->position();
        if (length % 2 == 1 && length > 1) {
            length--;
        }

        List<uint8> result = length > 0 ? List<uint8>(length) : List<uint8>();
        uint8 index = 0;
        uint8 hex[2];

        while (canRead() && (length == 0 || result.size() < length)) {
            Number ch = read();
            if (delimiterStrategy.hasDelimiter(ch)) {
                if (!delimiterStrategy.isSkipDelimiters()) {
                    unread();
                }
                break;
            }
            if (ch == ' ') {
                continue;
            }
            hex[index++] = hexCharToValue(startPosition, ch).getUInt8();
            if (index >= 2) {
                result.add((hex[0] << 4) + hex[1]);
                index = 0;
            }
        }

        if (index == 1) {
            result.add(hex[0]);
        }

        return std::move(result);
    }

    List<Number> ReaderInputStream::readNumberList(uintmax length, const DelimiterStrategy& delimiterStrategy, Number numberDelimiter) {
        uintmax startPosition = stream->position();
        List<Number> result = length > 0 ? List<Number>(length) : List<Number>();

        DelimiterStrategy numberStrategy = delimiterStrategy.plus(numberDelimiter, false);
        bool withBrackets = false;
        while (canRead() && (length == 0 || result.size() < length)) {
            Number ch = read();
            if (ch == '[') {
                if (withBrackets || result.size() > 0) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format");
                }

                withBrackets = true;
                numberStrategy.add(']');
                Number nextCh = read();
                unread();
                if (nextCh >= '0' && nextCh <= '9') {
                    try {
                        result.add(readNumber(numberStrategy, false));
                    }
                    catch (Exception& e) {
                        throw createException3("ReaderInputStream",
                            "Can not parse number",
                            new Exception(std::move(e)));
                    }
                }
            } else if (ch == ']') {
                if (!withBrackets) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format");
                }
                if (canRead() && delimiterStrategy.isSkipDelimiters()) {
                    if (!delimiterStrategy.hasDelimiter(read())) {
                        unread();
                    }
                }
                break;
            } else if (delimiterStrategy.hasDelimiter(ch)) {
                if (withBrackets) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format. Miss close bracket");
                }
                if (!delimiterStrategy.isSkipDelimiters()) {
                    unread();
                }
                break;
            } else {
                if (!numberStrategy.hasDelimiter(ch)) {
                    unread();
                }
                try {
                    result.add(readNumber(numberStrategy, true));
                }
                catch (Exception& e) {
                    stream->position(startPosition);
                    throw createException3("ReaderInputStream", "Can not parse number", new Exception(std::move(e)));
                }
            }
        }

        return std::move(result);
    }

    template <typename T>
    List<T> ReaderInputStream::readList(T& (*valueReader)(String&), uintmax length, const DelimiterStrategy& delimiterStrategy, Number elementDelimiter) {
        uintmax startPosition = stream->position();

        List<T> result = length > 0 ? List<T>(length) : List<T>();
        DelimiterStrategy elementStrategy = delimiterStrategy.plus(elementDelimiter, false);
        bool withBrackets = false;
        while (canRead() && (length == 0 || result.size() < length)) {
            Number ch = read();
            if (ch == '[') {
                if (withBrackets || result.size() > 0) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format");
                }

                withBrackets = true;
                elementStrategy.add(']');
            } else if (ch == ']') {
                if (!withBrackets) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format");
                }
                if (canRead() && !delimiterStrategy.isSkipDelimiters()) {
                    if (!delimiterStrategy.hasDelimiter(read())) {
                        unread();
                    }
                }
                break;
            } else if (delimiterStrategy.hasDelimiter(ch)) {
                if (withBrackets) {
                    stream->position(startPosition);
                    throw createException2("ReaderInputStream", "Wrong list format. Miss close bracket");
                }
                if (!delimiterStrategy.isSkipDelimiters()) {
                    unread();
                }
                break;
            } else {
                if (!elementStrategy.hasDelimiter(ch)) {
                    unread();
                }
                try {
                    result.add(valueReader(readString(0, elementStrategy, false)));
                }
                catch (Exception& e) {
                    stream->position(startPosition);
                    throw createException3("ReaderInputStream",
                        "Can not parse value",
                        new Exception(std::move(e)));
                }
            }
        }

        return std::move(result);
    }

};

