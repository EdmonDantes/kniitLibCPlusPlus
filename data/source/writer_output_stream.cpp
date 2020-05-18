/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */

#include <fstream>
#include "../writer_output_stream.h"

KNIIT_LIB_NAMESPACE {
    WriterOutputStream::WriterOutputStream(std::string fileName, bool append) {
        open(fileName, append);
    }

    WriterOutputStream::WriterOutputStream(WriterOutputStream&& reader) {
        operator=(std::move(reader));
    }

    bool WriterOutputStream::open(std::string& fileName, bool append) {
        auto* stream = append ? new std::ofstream(fileName, std::fstream::app) : new std::ofstream(fileName);
        if (stream->is_open() && OutputCStream::open(stream)) {
            return true;
        } else {
            delete stream;
            return false;
        }
    }

    WriterOutputStream& WriterOutputStream::operator=(WriterOutputStream&& reader) {
        OutputStream::operator=(std::move(reader));
        return *this;
    }

    bool WriterOutputStream::writeBoolean(bool value, bool isWord, bool upperCase, bool unicode, bool utf8, ByteOrder byteOrder) {
        if (isWord) {
            if (upperCase) {
                return writeString(value ? "TRUE" : "FALSE", unicode, utf8, byteOrder);
            } else {
                return writeString(value ? "true" : "false", unicode, utf8, byteOrder);
            }
        } else {
            return writeString(value ? "1" : "0", unicode, utf8, byteOrder);
        }
    }

    bool WriterOutputStream::writeASCIIChar(char ch) {
        uint8_t tmp = ch;
        return write(tmp);
    }

    bool WriterOutputStream::writeUnicodeChar(Number ch, bool utf8, ByteOrder byteOrder) {
        uint8_t bytes[4];
        unsigned int length = 0;
        unsigned int maxBytes = 0;
        unsigned int countBytes = 0;

        if (utf8) {
            if (ch > 0x7f) {
                uintmax _ch = ch.getUInt();
                if (ch > 0x7ff) {
                    if (ch > 0xffff) {
                        maxBytes = 21;
                        length = 4;
                        countBytes = 3;
                        bytes[0] = 0xF0u | (_ch >> (maxBytes - countBytes));
                    } else {
                        maxBytes = 16;
                        length = 3;
                        countBytes = 4;
                        bytes[0] = 0xE0u | (_ch >> (maxBytes - countBytes));
                    }
                } else {
                    maxBytes = 11;
                    length = 2;
                    countBytes = 5;
                    bytes[0] = 0xC0u | (_ch >> (maxBytes - countBytes));
                }

                for (int i = 1; i < length; i++) {
                    countBytes += 6;
                    bytes[i] = 0x80u | ((_ch >> (maxBytes - countBytes)) & 0x3Fu);
                }
            } else {
                length = 1;
                bytes[0] = ch.getUInt8();
            }

            return write(bytes, length, BIG_ENDIAN);
        } else {
            if (ch > 0xffff) {
                ch -= 0x10000;
                uintmax firstNumber = (ch.getUInt() >> 10);
                uintmax secondNumber = ch.getUInt() & 0x3FF;
                firstNumber += 0xD800;
                secondNumber += 0xDC00;
                bytes[0] = (firstNumber >> 8);
                bytes[1] = (firstNumber << 8) >> 8;

                write(bytes, 2, byteOrder);

                bytes[0] = (secondNumber >> 8);
                bytes[1] = (secondNumber << 8) >> 8;

                write(bytes, 2, byteOrder);
                return true;
            } else {
                length = 2;
                uint16_t _ch = ch.getUInt16();
                bytes[0] = _ch >> 8;
                bytes[1] = (_ch << 8) >> 8;
            }
        }

        return write(bytes, length, byteOrder);
    }

    bool WriterOutputStream::writeChar(Number ch, bool unicode, bool utf8, ByteOrder byteOrder) {
        if (unicode) {
            return writeUnicodeChar(ch, utf8, byteOrder);
        } else {
            return writeASCIIChar(ch.getUInt8());
        }
    }

    bool WriterOutputStream::writeASCIIString(std::string str) {
        uintmax startPosition = position();
        for (int i = 0; i < str.length(); i++) {
            if (!writeASCIIChar(str[i])) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    bool WriterOutputStream::writeUnicodeString(List<Number>& str, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        for (int i = 0; i < str.size(); i++) {
            if (!writeUnicodeChar(str[i], utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    bool WriterOutputStream::writeInt(Number value, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        intmax number = value.getInt();
        if (number < 0) {
            if (!writeChar('-', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            number = -number;
        } else if (number == 0) {
            if (!writeChar('0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            return true;
        }

        uintmax tmp = 0;
        while (number > 0) {
            tmp *= 10;
            tmp += number % 10;
            number /= 10;
        }

        while (tmp > 0) {
            if (!writeChar(tmp % 10 + '0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            tmp /= 10;
        }
        return true;
    }

    bool WriterOutputStream::writeUInt(Number value, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        uintmax number = value.getUInt();
       if (number == 0) {
            if (!writeChar('0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            return true;
        }

        uintmax tmp = 0;
        while (number > 0) {
            tmp *= 10;
            tmp += number % 10;
            number /= 10;
        }

        while (tmp > 0) {
            if (!writeChar(tmp % 10 + '0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            tmp /= 10;
        }
        return true;
    }

    bool WriterOutputStream::writeNumber(Number value, uint8_t maxCharAfterPoint, bool unicode, bool utf8, ByteOrder byteOrder) {
        if (value.isInteger()) {
            if (value.isUInt()) {
                return writeUInt(value, unicode, utf8, byteOrder);
            } else {
                return writeInt(value, unicode, utf8, byteOrder);
            }
        }

        uintmax startPosition = position();

        double number = value.getDouble();

        if (number < 0) {
            if (!writeChar('-', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            number = -number;
        } else if (number == 0) {
            if (!writeChar('0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            return true;
        }

        auto integerNumber = (uintmax) number;
        number -= integerNumber;

        std::string str;
        while (integerNumber > 0) {
            str += (integerNumber % 10) + '0';
            integerNumber /= 10;
        }

        for (int i = str.size() - 1; i > -1; i--) {
            if (!writeChar(str[i], unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
        }

        if (number > 0) {
            if (!writeChar('.', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
        }

        int index = 0;
        while (number > 0 && index < maxCharAfterPoint) {
            number *= 10;
            auto tmp = (uintmax) number;
            if (!writeChar(tmp + '0', unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
            number -= tmp;
            index++;
        }
        return true;
    }

    bool WriterOutputStream::writeString(List<Number>& str, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        for (int i = 0; i < str.size(); i++) {
            if (!writeChar(str[i], unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    bool WriterOutputStream::writeString(std::string str, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        for (char ch : str) {
            if (!writeChar(ch, unicode, utf8, byteOrder)) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    char hexToChar(uint8_t halfByte) {
        if (halfByte < 10) {
            return halfByte + '0';
        } else {
            return 'A' + (halfByte - 10);
        }
    }

    bool WriterOutputStream::writeColor(Number value, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        if (!writeChar('#')) {
            position(startPosition);
            return false;
        }

        uintmax color = value.getUInt();
        uintmax mask = 0xF0000000;
        uintmax shift = 28;
        while (mask > 0) {
            if (!writeChar(hexToChar((color & mask) >> shift))) {
                position(startPosition);
                return false;
            }
            mask = mask >> 4;
            shift -= 4;
        }

        return true;
    }

    bool
    WriterOutputStream::writeHex(List<uint8_t>& value, uintmax length, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        uintmax count = 0;
        for (int i = 0; i < value.size() && (length < 1 || count < length); i++) {
            uint8_t tmp = value[i];
            if (!writeChar(hexToChar(tmp >> 4))) {
                position(startPosition);
                return false;
            }
            count++;
            if (length < 1 || count < length) {
                if (!writeChar(hexToChar(tmp & 0xF))) {
                    position(startPosition);
                    return false;
                }
            }
        }
        return true;
    }

    bool WriterOutputStream::writePoint(List<Number>& value, uint8_t maxCharAfterPoint, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        if (!writeChar('(')) {
            position(startPosition);
            return false;
        }

        for (int i = 0; i < value.size(); i++) {
            if (!(writeNumber(value[i], maxCharAfterPoint, unicode, utf8, byteOrder) && (i == value.size() - 1 ? writeChar(')') : writeChar(';')))) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    bool WriterOutputStream::writeList(List<Number>& value, uint8_t maxCharAfterPoint, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        if (!writeChar('[')) {
            position(startPosition);
            return false;
        }

        for (int i = 0; i < value.size(); i++) {
            if (!(writeNumber(value[i], maxCharAfterPoint, unicode, utf8, byteOrder) && (i == value.size() - 1 ? writeChar(']') : writeChar(';')))) {
                position(startPosition);
                return false;
            }
        }
        return true;
    }

    bool WriterOutputStream::writeSet(Set<Number>& value, uint8_t maxCharAfterPoint, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();
        if (!writeChar('{')) {
            position(startPosition);
            return false;
        }

        auto it = value.iterator();
        while (it->hasNext()) {
            if (!(writeNumber(it->next(), maxCharAfterPoint, unicode, utf8, byteOrder) && writeChar(';'))) {
                position(startPosition);
                return false;
            }
        }

        if (value.size() > 0) {
            position(position() - 1);
        }

        if (!writeChar('}')) {
            position(startPosition);
            return false;
        }
        return true;
    }

    bool WriterOutputStream::writeMatrix(MutableMatrix<Number> &matrix, uint8_t maxCharAfterPoint, bool unicode, bool utf8, ByteOrder byteOrder) {
        uintmax startPosition = position();

        uintmax size = matrix.minLines();
        for (int i = 0; i < size; i++) {
            if (!(writeList(matrix.getLine(i), maxCharAfterPoint, unicode, utf8, byteOrder) && (i == size - 1 ? true : writeChar('\n', unicode, utf8, byteOrder)))) {
                position(startPosition);
                return false;
            }
        }

        return true;
    }


};