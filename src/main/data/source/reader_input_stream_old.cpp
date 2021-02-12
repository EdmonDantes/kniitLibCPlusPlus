///*
// *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
// *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
// */
//#include "../../core/exception.h"
//#include "../reader_input_stream_old.h"
//#include <fstream>
//#include <algorithm>
//
//#define min(a, b) (a) < (b) ? (a) : (b)
//#define max(a, b) (a) > (b) ? (a) : (b)
//
//using namespace std;
//
//KNIIT_LIB_NAMESPACE {
//    ReaderInputStream::ReaderInputStream(std::string fileName) {
//        open(fileName);
//    }
//
//    bool ReaderInputStream::open(std::string& fileName) {
//        auto* stream = new std::ifstream(fileName);
//        if (stream->is_open() && InputCStream::open(stream)) {
//            return true;
//        } else {
//            delete stream;
//            return false;
//        }
//    }
//
//    void ReaderInputStream::setSkip(bool skip) {
//        this->skip = skip;
//    }
//
//    bool ReaderInputStream::readBoolean(bool caseSensitive, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        std::string word;
//        while (canRead()) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if ((ch == ' ' || ch == '\n') && word.length() < 1) {
//                continue;
//            }
//
//            if (ch >= '0' && ch <= '1') {
//                if (word.length() < 1) {
//                    return ch == '1';
//                } else {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            } else if (caseSensitive && ch >= 'a' && ch <= 'z') {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//
//            word += tolower(ch.getInt32());
//
//            if (word.length() == 4 && word == "true") {
//                return true;
//            } else if (word.length() > 4) {
//                if (word == "false") {
//                    return false;
//                } else {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            }
//        }
//
//        if (!skip) {
//            position(startPosition);
//        }
//        throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//    }
//
//    Number ReaderInputStream::readInt32(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::INT32, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readUInt32(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::UINT32, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readInt(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::INT, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readUInt(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::UINT, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readFloat(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::FLOAT, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readDouble(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return readNumber(DataTypes::DOUBLE, unicode, utf8, byteOrder);
//    }
//
//    Number ReaderInputStream::readNumber(DataType type, bool unicode, bool utf8, ByteOrder byteOrder, bool throwIfNotRead) {
//        if (!type.isSimple() || type == DataTypes::BOOLEAN || type == DataTypes::CHAR || type == DataTypes::UNICODE_CHAR) {
//            return Number();
//        }
//
//        uintmax startPosition = position();
//
//        bool negate = false;
//        bool realPart = false;
//        Number number;
//        if (type == DataTypes::INT32) {
//            number = Number((int32_t) 0, true);
//        } else if (type == DataTypes::UINT32) {
//            number = Number((uint32_t) 0, true);
//        } else if (type == DataTypes::INT) {
//            number = Number((intmax) 0, true);
//        } else if (type == DataTypes::UINT) {
//            number = Number((uintmax) 0, true);
//        } else if (type == DataTypes::FLOAT) {
//            number = Number(0.f, true);
//        } else if (type == DataTypes::DOUBLE) {
//            number = Number(0., true);
//        } else {
//            number = Number(0);
//        }
//        int count_number = 0;
//        int count_real = 0;
//        while (canRead()) {
//            uintmax prevPosition = position();
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if ((ch == ' ' || ch == '\n')) {
//                if (count_number < 1) {
//                    continue;
//                } else {
//                    position(prevPosition);
//                    break;
//                }
//            }
//
//            if ((ch == '-' || ch == '+') && count_number < 1) {
//                negate = ch == '-';
//            } else if (ch >= '0' && ch <= '9') {
//                if (realPart) {
//                    float floatTmp = 0.f;
//                    double doubleTmp = 0.0;
//
//                    doubleTmp = ch.getInt8() - '0';
//                    floatTmp = (float) doubleTmp;
//
//                    for (int i = 0; i <= count_real; i++) {
//                        if (count_real >= 6) {
//                            doubleTmp /= 10;
//                        } else {
//                            floatTmp /= 10;
//                        }
//                    }
//
//                    number += (count_real >= 6 ? doubleTmp : floatTmp);
//                    count_real++;
//                } else {
//                    number *= 10;
//                    number += ch - '0';
//                }
//                count_number++;
//            } else if ((ch == ',' || ch == '.') && !realPart) {
//                realPart = true;
//                continue;
//            } else {
//                position(prevPosition);
//                break;
//            }
//        }
//
//        if (count_number < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            if (throwIfNotRead) {
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//            } else {
//                return Number();
//            }
//        } else {
//            return negate ? -number : number;
//        }
//    }
//
//    char ReaderInputStream::readASCIIChar() {
//        return read();
//    }
//
//    Number ReaderInputStream::readUnicodeChar(bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        uint8_t bytes[4];
//        if (utf8) {
//
//            // TODO: add UTF-8 depending from byte order
//
//            int additional = 0;
//            uint32_t tmp;
//            uint8_t firstByte = read();
//            if ((firstByte & 0x7F) == firstByte) {
//                return firstByte;
//            } else if ((firstByte & 0xDF) == firstByte) {
//
//                additional = 1;
//                tmp = (firstByte & 0x1F) << 6;
//
//            } else if ((firstByte & 0xEF) == firstByte) {
//
//                additional = 2;
//                tmp = (firstByte & 0x0F) << 12;
//
//            } else if ((firstByte & 0xF7) == firstByte) {
//
//                additional = 3;
//                tmp = (firstByte & 0x07) << 18;
//
//            } else {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//
//            for (int i = 0; i < additional; i++) {
//                uint8_t additionalByte = read();
//                if ((additionalByte & 0xBF) == additionalByte) {
//                    tmp += (additionalByte & 0x3F) << (additional - i - 1) * 6;
//                } else {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            }
//            return tmp;
//        } else {
//            read(&bytes[0], 2, byteOrder);
//
//            uint16_t firstCode = (bytes[0] << 8) + bytes[1];
//            if (firstCode >= 0xD800 && firstCode <= 0xDFFF) {
//                if (firstCode > 0xDBFF) {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//
//                read(&bytes[2], 2, byteOrder);
//                uint16_t secondCode = ((uint16_t) bytes[2] << 8) | bytes[3];
//
//                if (secondCode < 0xDC00 && secondCode > 0xDFFF) {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//
//                return ((uintmax) ((firstCode - 0xD800) << 10) | (secondCode - 0xDC00)) + 0x10000;
//            }
//
//            return firstCode;
//        }
//    }
//
//    Number ReaderInputStream::readChar(bool unicode, bool utf8, ByteOrder byteOrder) {
//        return unicode ? readUnicodeChar(utf8, byteOrder) : readASCIIChar();
//    }
//
//    std::string ReaderInputStream::readASCIIString(uintmax length, bool addEndChar, char endChar, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        std::stringstream ss;
//
//        for (uintmax i = 0; (length < 1 || i < length) && canRead(); i++) {
//            char ch = readASCIIChar();
//
//            if (ch == endChar) {
//                if (addEndChar) {
//                    ss << ch;
//                }
//                break;
//            } else {
//                ss << ch;
//            }
//        }
//
//        std::string result = ss.str();
//
//        if (result.length() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        }
//
//        if (byteOrder == LITTLE_ENDIAN) {
//            std::reverse(result.begin(), result.end());
//        }
//        return result;
//    }
//
//    String ReaderInputStream::readUnicodeString(uintmax length, bool utf8, bool addEndChar, Number endChar, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        String result;
//
//        for (uintmax i = 0; (length < 1 || i < length) && canRead(); i++) {
//            Number ch = readUnicodeChar(utf8, byteOrder);
//
//            if (ch == endChar) {
//                if (addEndChar) {
//                    result += ch;
//                }
//                break;
//            } else {
//                result += ch;
//            }
//        }
//
//        if (result.size() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        }
//
//        if (byteOrder == LITTLE_ENDIAN) {
//            return std::move(result.reverse());
//        }
//
//        return std::move(result);
//    }
//
//    int8_t hexToNumber(char ch) {
//        ch = tolower(ch);
//        if (ch >= '0' && ch <= '9') {
//            return ch - '0';
//        } else if (ch >= 'a' && ch <= 'f') {
//            return ch - 'a' + 10;
//        } else {
//            return -1;
//        }
//    }
//
//    Number ReaderInputStream::readColor(uint8_t zeroAlpha, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        bool continueRead = true;
//        bool readFirstChar = false;
//        bool isHex = false;
//        bool inBreaks = false;
//        std::string word;
//        Number numbers[4];
//        int index = 0;
//
//        while (continueRead && canRead()) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if (ch == ' ' || ch == '\n') {
//                if (!readFirstChar || inBreaks) {
//                    continue;
//                } else if (readFirstChar && isHex) {
//                    continueRead = false;
//                    switch (word.length()) {
//                        case 3:
//                            return (((uint32_t)zeroAlpha) << 24) | (((uint32_t) (hexToNumber(word[0]) / 15.0 * 255.0)) << 16) | (((uint32_t) (hexToNumber(word[1]) / 15.0 * 255.0)) << 8) | ((uint32_t) (hexToNumber(word[2]) / 15.0 * 255.0));
//                        case 4:
//                            return (((uint32_t) (hexToNumber(word[0]) / 15.0 * 255.0)) << 24) | (((uint32_t) (hexToNumber(word[1]) / 15.0 * 255.0)) << 16) | (((uint32_t) (hexToNumber(word[2]) / 15.0 * 255.0)) << 8) | ((uint32_t) (hexToNumber(word[3]) / 15.0 * 255.0));
//                        case 6:
//                            return (((uint32_t) zeroAlpha) << 24)
//                                   | (((uint32_t) hexToNumber(word[0])) << 20) | (((uint32_t) hexToNumber(word[1])) << 16)
//                                   | (((uint32_t) hexToNumber(word[2])) << 12) | (((uint32_t) hexToNumber(word[3])) << 8)
//                                   | (((uint32_t) hexToNumber(word[4])) << 4) | ((uint32_t) hexToNumber(word[5]));
//                        case 8:
//                            return (((uint32_t) hexToNumber(word[0])) << 28) | (((uint32_t) hexToNumber(word[1])) << 24)
//                                   | (((uint32_t) hexToNumber(word[2])) << 20) | (((uint32_t) hexToNumber(word[3])) << 16)
//                                   | (((uint32_t) hexToNumber(word[4])) << 12) | (((uint32_t) hexToNumber(word[5])) << 8)
//                                   | (((uint32_t) hexToNumber(word[6])) << 4) | ((uint32_t) hexToNumber(word[7]));
//                        default:
//                            if (!skip) {
//                                position(startPosition);
//                            }
//                            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                    }
//                }
//            }
//
//            if (!readFirstChar) {
//                readFirstChar = true;
//                if (ch == '#') {
//                    isHex = true;
//                    continue;
//                } else if (tolower(ch.getInt()) != 'r' && tolower(ch.getInt()) != 'a') {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            }
//
//
//            if (isHex) {
//                if (hexToNumber(ch.getInt8()) < 0) {
//                    if (!skip) {
//                        position(startPosition);
//                    }
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                } else {
//                    word += ch.getInt8();
//                }
//            } else {
//                if (!inBreaks) {
//                    if (ch != '(') {
//                        word += tolower(ch.getInt8());
//                    } else {
//                        if (word != "rgb" && word != "argb") {
//                            if (!skip) {
//                                position(startPosition);
//                            }
//                            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                        }
//
//                        inBreaks = true;
//                        numbers[index++] = readNumber(DataTypes::NUMBER, unicode, utf8, byteOrder);
//                    }
//                } else {
//                    if (ch == ';') {
//                        numbers[index++] = readNumber(DataTypes::NUMBER, unicode, utf8, byteOrder);
//                    } else if (ch == ')') {
//                        inBreaks = false;
//                        continueRead = false;
//
//                        bool haveInt = false;
//                        for (int i = 0; i < index; i++) {
//                            if (numbers[i].isInteger()) {
//                                haveInt = true;
//                                break;
//                            }
//                        }
//
//                        for (int i = 0; i < index; i++) {
//                            if (haveInt) {
//                                numbers[i] = max(min(numbers[i], 255), 0);
//                            } else {
//                                numbers[i] = max(min(numbers[i], 1.0), 0.0);
//                            }
//                        }
//
//                        switch (index) {
//                            case 3:
//                                if (haveInt) {
//                                    return (Number((uint32_t) zeroAlpha) << 24) | (numbers[0] << 16) | (numbers[1] << 8) | (numbers[2]);
//                                } else {
//                                    return (Number((uint32_t) zeroAlpha) << 24) | ((numbers[0] * 255.0).getUInt() << 16) | ((numbers[1] * 255.00).getUInt() << 8) | (numbers[2] * 255.0).getUInt();
//                                }
//                            case 4:
//                                if (haveInt) {
//                                    return (numbers[0] << 24) | (numbers[1] << 16) | (numbers[2] << 8) | numbers[3];
//                                } else {
//                                    return ((numbers[0] * 255.0).getUInt() << 24) | ((numbers[1] * 255.00).getUInt() << 16) | ((numbers[2] * 255.0).getUInt() << 8) | (numbers[3] * 255.0).getUInt();
//                                }
//                            default:
//                                if (!skip) {
//                                    position(startPosition);
//                                }
//                                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                        }
//                    } else {
//                        if (!skip) {
//                            position(startPosition);
//                        }
//                        throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                    }
//                }
//            }
//        }
//
//        if (!skip) {
//            position(startPosition);
//        }
//        throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//    }
//
//    List<uint8_t> ReaderInputStream::readHex(uintmax length, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        List<uint8_t> hex;
//
//        uint8_t tmp = 0;
//        for (uintmax i = 0; (length < 1 || i < length) && canRead(); i++) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if ((ch == ' ' || ch == '\n')) {
//                if (hex.size() < 1) {
//                    continue;
//                } else {
//                    break;
//                }
//            }
//
//            int8_t hexToNum = hexToNumber(ch.getInt8());
//            if (hexToNum < 0) {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//
//            if (tmp == 0) {
//                tmp += hexToNum << 8;
//            } else {
//                tmp += hexToNum;
//                hex.add(tmp);
//                tmp = 0;
//            }
//        }
//
//        if (hex.size() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        }
//
//        return hex;
//    }
//
//    List<Number> ReaderInputStream::readPoint(uintmax length, DataType inputType, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//        List<Number> result = length > 0 ? List<Number>(length) : List<Number>();
//
//        bool inBraces = false;
//
//        while (canRead()) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if ((ch == ' ' || ch == '\n') && !inBraces) {
//                continue;
//            } else if (ch == '\n') {
//                break;
//            } else if (ch == '(' && !inBraces) {
//                inBraces = true;
//                result.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == ';' && inBraces) {
//                result.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == ')' && inBraces) {
//                break;
//            } else {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//        }
//
//        if (result.size() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        } else if (length < 1 || result.size() == length) {
//            return result;
//        } else {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//        }
//    }
//
//    List<Number> ReaderInputStream::readNumberList(uintmax maxLength, DataType inputType, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//
//        List<Number> result;
//
//        bool inBraces = false; // In braces or reading number without braces
//        bool withOutBraces = false;
//
//        while (canRead() && (maxLength < 1 || result.size() < maxLength)) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//            if (ch == ' ' || ch == '\n') {
//                if (inBraces && withOutBraces) {
//                    break;
//                } else {
//                    continue;
//                }
//            } else if (ch == '[' && !withOutBraces && !inBraces) {
//                inBraces = true;
//                result.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == ']' && !withOutBraces && inBraces) {
//                break;
//            } else if (ch >= '0' && ch <= '9' && !inBraces) {
//                position(position() - 1);
//                withOutBraces = true;
//                inBraces = true;
//                result.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == ';' && inBraces) {
//                result.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//        }
//
//        if (result.size() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        } else {
//            return result;
//        }
//    }
//
//    Set<Number> ReaderInputStream::readSet(bool skipNotUnique, int length, DataType inputType, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//
//        Set<Number> result;
//
//        bool inBraces = false; // In braces or reading number without braces
//        bool withOutBraces = false;
//
//        while (canRead() && (length < 1 || result.size() < length)) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//            if (ch == ' ' || ch == '\n') {
//                if (inBraces && withOutBraces) {
//                    break;
//                } else {
//                    continue;
//                }
//            } else if (ch == '{' && !withOutBraces && !inBraces) {
//                inBraces = true;
//                if (!result.add(readNumber(inputType, unicode, utf8, byteOrder, false)) && !skipNotUnique) {
//                    position(startPosition);
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            } else if (ch == '}' && !withOutBraces && inBraces) {
//                break;
//            } else if (ch >= '0' && ch <= '9' && !inBraces) {
//                position(position() - 1);
//                withOutBraces = true;
//                inBraces = true;
//                if (!result.add(readNumber(inputType, unicode, utf8, byteOrder, false)) && !skipNotUnique) {
//                    position(startPosition);
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            } else if (ch == ';' && inBraces) {
//                if (!result.add(readNumber(inputType, unicode, utf8, byteOrder, false)) && !skipNotUnique) {
//                    position(startPosition);
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                }
//            } else {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//        }
//
//        if (result.size() < 1) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        } else {
//            return result;
//        }
//    }
//
//    MutableMatrix<Number> ReaderInputStream::readMatrix(uintmax lines, uintmax columns, DataType inputType, bool unicode, bool utf8, ByteOrder byteOrder) {
//        uintmax startPosition = position();
//
//        MutableMatrix<Number> result;
//        // For matrix
//        bool readMetadata = false;
//        bool readColumns = false;
//        bool prevNextLine = false;
//
//        // For tmp
//        bool inBraces = false; // In braces or reading number without braces
//        bool withOutBraces = false;
//
//        List<Number> tmp;
//
//        while(canRead()) {
//            Number ch = readChar(unicode, utf8, byteOrder);
//
//            if (ch == '\n') {
//                if (prevNextLine) {
//                    break;
//                }
//
//                if (tmp.size() > 0) {
//                    readColumns ? result.addColumn(tmp) : result.addLine(tmp);
//                    tmp.clear();
//                }
//
//                prevNextLine = true;
//                inBraces = false;
//                withOutBraces = false;
//                continue;
//            } else if (ch != ' ') {
//                prevNextLine = false;
//            }
//
//            if (ch == ' ') {
//                continue;
//            }
//
//            if (ch == 'l' || ch == 'L' || ch == 'c' || ch == 'C') {
//                if (readMetadata) {
//                    position(startPosition);
//                    throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//                } else {
//                    if (ch == 'c' || ch == 'C') {
//                        readColumns = true;
//                    }
//                    readMetadata = true;
//                }
//            } else if (ch == '{' || ch == '[' && !withOutBraces && !inBraces) {
//                readMetadata = true;
//                inBraces = true;
//                tmp.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == '}' || ch == ']' && !withOutBraces && inBraces) {
//                readMetadata = true;
//                inBraces = false;
//                continue;
//            } else if (ch >= '0' && ch <= '9' && !inBraces) {
//                readMetadata = true;
//                position(position() - 1);
//                withOutBraces = true;
//                inBraces = true;
//                tmp.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else if (ch == ';' && inBraces) {
//                readMetadata = true;
//                tmp.add(readNumber(inputType, unicode, utf8, byteOrder, false));
//            } else {
//                if (!skip) {
//                    position(startPosition);
//                }
//                throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_FORMAT_ERROR);
//            }
//
//        }
//
//        if (tmp.size() > 0) {
//            readColumns ? result.addColumn(tmp) : result.addLine(tmp);
//        }
//
//        if (result.minLines() < lines || result.minColumns() < columns) {
//            if (!skip) {
//                position(startPosition);
//            }
//            throw createException2("ReaderInputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
//        } else {
//            return result;
//        }
//    }
//
//    ReaderInputStream::~ReaderInputStream() {
//        this->close();
//    }
//
//    ReaderInputStream::ReaderInputStream() {
//        this->stream = 0;
//    }
//
//    ReaderInputStream::ReaderInputStream(ReaderInputStream &&reader) : InputCStream(std::move(reader)){
//        operator=(std::move(reader));
//    }
//
//    ReaderInputStream &ReaderInputStream::operator=(ReaderInputStream&& reader) {
//        InputStream::operator=(std::move(reader));
//        this->skip = reader.skip;
//        reader.skip = false;
//        return *this;
//    }
//
//
//}