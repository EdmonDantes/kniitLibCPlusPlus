/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include "algorithm"
#include "../reader_input_stream.h"

KNIIT_LIB_NAMESPACE {

    Number ReaderInputStream::read() {
        if (!stream->canRead()) {
            throw createException2("ReaderInputStream", "Can not read stream");
        }

        return codec->decodeOne(stream, byteOrder);
    }

    void ReaderInputStream::init(InputStream<uint8_t>* stream, const Codec* codec, ByteOrder byteOrder)  {
        this->stream = stream;
        this->codec = codec;
        this->byteOrder = byteOrder;
    }

    ReaderInputStream::ReaderInputStream(InputStream<uint8_t>* stream, const Codec* codec, ByteOrder byteOrder) {
        init(stream, codec, byteOrder);
    }

    bool ReaderInputStream::canRead() {
        return this->stream->canRead() && codec != nullptr;
    }

    Number ReaderInputStream::readChar() {
        return read();
    }

    String ReaderInputStream::readString(uintmax length, Number lastChar, bool addLastChar) {
        String result;
        Number ch = readChar();
        while (result.size() < length || length < 1) {
            if (ch == lastChar) {
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

    Number ReaderInputStream::readNumber(Number delimiter) {
        uintmax startPosition = stream->position();

        int decimalPartShift = -1;
        bool sign = false;

        uint8_t number_value[std::max(sizeof(uintmax), sizeof(double))];
        void* number = &number_value;

        *((uintmax*) number) = 0;

        while (canRead()) {
            Number ch = readChar();

            if (ch >= '0' && ch <= '9') {
                if (decimalPartShift > -1) {
                    double decimalPart = ch.getInt() - '0';
                    for (int i = decimalPartShift++; i > -1; i--) {
                        decimalPart /= 10;
                    }
                    *((double*) number) += decimalPart;
                } else {
                    *((intmax* )number) *= 10;
                    *((intmax*) number) += ch.getInt() - '0';
                }
            } else if ((ch == ',' || ch == '.') && decimalPartShift < 0) {
                decimalPartShift = 0;
                *((double*)number) = *((intmax*) number);
            } else if (ch == '-' && (stream->position() - startPosition) < 2) {
                sign = true;
            } else if (ch == delimiter) {
                stream->position(stream->position() - 1);
                break;
            } else {
                stream->position(startPosition);
                throw createException2("ReaderInputStream", "Wrong number format");
            }
        }

        Number result = decimalPartShift > -1 ? Number(*((double*) number)) : Number((*((uintmax*) number)));
        return sign ? -result : result;
    }

    Number ReaderInputStream::readColor(Number delimiter) {
        uintmax startPosition = stream->position();

        int8_t countCharacterInSharpType = -1;
        uint8_t args[8];
        String word;

        while (canRead()) {
            Number ch = readChar();

            if (ch == '#') {
                if (word.isEmpty()) {
                    countCharacterInSharpType = 0;
                    continue;
                } else {
                    stream->position(startPosition);
                    createException2("ReaderInputStream", "Wrong color format");
                }
            }

            if (countCharacterInSharpType > -1) {
                uint8_t tmp = ch.getUInt8();
                if (ch >= '0' && ch <= '9') {
                    tmp -= '0';
                } else if (ch >= 'a' && ch <= 'f') {
                    tmp -= 'a' - 10;
                } else if (ch >= 'A' && ch <= 'F') {
                    tmp -= 'A' - 10;
                } else if (ch == delimiter) {
                    break;
                } else {
                    stream->position(startPosition);
                    createException2("ReaderInputStream", "Wrong color format");
                }

                args[countCharacterInSharpType] = tmp;
                countCharacterInSharpType++;
            } else {
                if (ch == '(') {
                    word = word.toLower();
                    if (word == "rgb") {
                        Number r = readNumber(';');
                        read();
                        Number g = readNumber(';');
                        read();
                        Number b = readNumber(')');
                        read();

                        if (r.isDouble() || g.isDouble() || b.isDouble()) {
                            r *= 255;
                            g *= 255;
                            b *= 255;
                        }

                        return ((r.getUInt() & 0xff) << 16)  + ((g.getUInt() & 0xff) << 8) + (b.getUInt() & 0xff);
                    } else if (word == "argb") {
                        Number a = readNumber(';');
                        read();
                        Number r = readNumber(';');
                        read();
                        Number g = readNumber(';');
                        read();
                        Number b = readNumber(')');
                        read();

                        if (a.isDouble() || r.isDouble() || g.isDouble() || b.isDouble()) {
                            a *= 255;
                            r *= 255;
                            g *= 255;
                            b *= 255;
                        }

                        return ((a.getUInt() & 0xff) << 24) + ((r.getUInt() & 0xff) << 16)  + ((g.getUInt() & 0xff) << 8) + (b.getUInt() & 0xff);
                    } else {
                        stream->position(startPosition);
                        createException2("ReaderInputStream", "Wrong color format");
                    }
                } else {
                    word += ch;
                }


                if (word.size() > 4) {
                    stream->position(startPosition);
                    createException2("ReaderInputStream", "Wrong color format");
                }
            }
        }

        if (countCharacterInSharpType > -1) {
            if (countCharacterInSharpType == 8) {
                Number result = 0;
                for (int i = 0; i < 4; ++i) {
                    uint8_t tmp = (args[i * 2] << 4) + args[i * 2 + 1];
                    result += ((uintmax) tmp) << (24 - 8 * i);
                }
                return result;
            } else if (countCharacterInSharpType == 6) {
                Number result = 0;
                for (int i = 0; i < 3; ++i) {
                    uint8_t tmp = (args[i * 2] << 4) + args[i * 2 + 1];
                    result += ((uintmax) tmp) << (16 - 8 * i);
                }
                return result;
            } else if (countCharacterInSharpType == 4) {
                Number result = 0;
                for (int i = 0; i < 4; ++i) {
                    uint8_t tmp = 0xff * (args[i] / (float) 0xf);
                    result += ((uintmax) tmp) << (24 - 8 * i);
                }
                return result;
            } else if (countCharacterInSharpType == 3){
                Number result = 0;
                for (int i = 0; i < 3; ++i) {
                    uint8_t tmp = 0xff * (args[i] / (float) 0xf);
                    result += ((uintmax) tmp) << (16 - 8 * i);
                }
                return result;
            }
        }

        stream->position(startPosition);
        createException2("ReaderInputStream", "Wrong color format");
    }

};

