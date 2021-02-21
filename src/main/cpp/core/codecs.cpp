/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include "core/codecs.h"

KNIIT_LIB_NAMESPACE {
    namespace Codecs {

        List<uint8> CodecASCII::encodeOne(Number ch, ByteOrder byteOrder) const {
            List<uint8> result(1);
            result.add(ch.getUInt8());

            return std::move(result);
        }

        Number CodecASCII::decodeOne(InputStream<uint8>* in, ByteOrder byteOrder) const {
            if (!in->canRead()) {
                throw createException2("CodecASCII", "Can not read input stream");
            }

            return in->read();
        }

        List<uint8> CodecUTF8::encodeOne(Number ch, ByteOrder byteOrder) const {
            List<uint8> result(4);

            uint8 tmp[4];
            int length = 0;
            if (ch < 0x80) {
                length = 1;
                tmp[0] = ch.getUInt8();
            } else if (ch < 0x800) {
                length = 2;
                tmp[1] = 0x80 | (ch.getUInt32() & 0x3F);
                tmp[0] = 0xC0 | ((ch.getUInt32() >> 6) & 0x1F);
            } else if (ch < 0x10000) {
                length = 3;
                tmp[2] = 0x80 | (ch.getUInt32() & 0x3F);
                tmp[1] = 0x80 | ((ch.getUInt32() >> 6) & 0x3F);
                tmp[0] = 0xE0 | ((ch.getUInt32() >> 12) & 0x0F);
            } else {
                length = 4;
                tmp[3] = 0x80 | (ch.getUInt32() & 0x3F);
                tmp[2] = 0x80 | ((ch.getUInt32() >> 6) & 0x3F);
                tmp[1] = 0x80 | ((ch.getUInt32() >> 12) & 0x3F);
                tmp[0] = 0xF0 | ((ch.getUInt32() >> 18) & 0x07);
            }

            for (int j = 0; j < length; j++) {
                result.add(tmp[byteOrder == BIG_ENDIAN_BYTE_ORDER ? j : length - 1 - j]);
            }

            return std::move(result);
        }

        Number CodecUTF8::decodeOne(InputStream<uint8>* in, ByteOrder byteOrder) const {
            uint8 tmp[4];
            uint8 index = 0;
            /**
             * 1 bit - find 2 byte start
             * 2 bit - find 3 byte start
             * 3 bit - find 4 byte start
             */
            Status<uint8> status;

            while (in->canRead()) {
                if (index > 4) {
                    throw createException2("CodecUTF8", "Wrong UTF-8 format");
                }

                uint8 byte = in->read();
                if ((byte & 0x7F) == byte) {
                    if (!status.isEmpty() || index > 0) {
                        throw createException2("CodecUTF8", "Wrong UTF-8 format");
                    }

                    return byte;
                } else if ((byte & 0xE0) == 0xC0) {
                    if (!status.isEmpty() || index > 1) {
                        throw createException2("CodecUTF8", "Wrong UTF-8 format");
                    }

                    status.add(1);
                    tmp[index++] = byte;
                } else if ((byte & 0xF0) == 0xE0) {
                    if (!status.isEmpty() || index > 2) {
                        throw createException2("CodecUTF8", "Wrong UTF-8 format");
                    }

                    status.add(2);
                    tmp[index++] = byte;
                } else if ((byte & 0xF8) == 0xF0) {
                    if (!status.isEmpty() || index > 3) {
                        throw createException2("CodecUTF8", "Wrong UTF-8 format");
                    }

                    status.add(3);
                    tmp[index++] = byte;
                } else {
                    tmp[index++] = byte;
                }


                switch (index) {
                    case 2:
                        if (status.check(1)) {
                            uint16 ch = 0;
                            for (int i = 0; i < index; i++) {
                                uint8 byte = tmp[byteOrder == BIG_ENDIAN_BYTE_ORDER ? i : index - i - 1];
                                if ((byte & 0xC0) == 0x80) {
                                    ch = ch << 6;
                                    ch |= byte & 0x3F;
                                } else {
                                    ch = ch << 5;
                                    ch |= byte & 0x1F;
                                }
                            }
                            return ch;
                        }
                        break;
                    case 3:
                        if (status.check(2)) {
                            uint32 ch = 0;
                            for (int i = 0; i < index; i++) {
                                uint8 byte = tmp[byteOrder == BIG_ENDIAN_BYTE_ORDER ? i : index - i - 1];
                                if ((byte & 0xC0) == 0x80) {
                                    ch = ch << 6;
                                    ch |= byte & 0x3F;
                                } else {
                                    ch = ch << 4;
                                    ch |= byte & 0xF;
                                }
                            }
                            return ch;
                        }
                        break;
                    case 4:
                        if (status.check(3)) {
                            uint32 ch = 0;
                            for (int i = 0; i < index; i++) {
                                uint8 byte = tmp[byteOrder == BIG_ENDIAN_BYTE_ORDER ? i : index - i - 1];
                                if ((byte & 0xC0) == 0x80) {
                                    ch = ch << 6;
                                    ch |= byte & 0x3F;
                                } else {
                                    ch = ch << 3;
                                    ch |= byte & 0x7;
                                }
                            }
                            return ch;
                        } else {
                            throw createException2("CodecUTF8", "Wrong UTF-8 format");
                        }
                }
            }

            throw createException2("CodecUTF8", "Can not read input stream");
        }

        List<uint8> CodecUTF16::encodeOne(Number ch, ByteOrder byteOrder) const {
            List<uint8> result(4);
            uint16 tmp[2];
            int length = 0;

            if (ch < 0x10000) {
                length = 2;
                tmp[0] = ch.getUInt16();
            } else {
                length = 4;
                ch -= 0x10000;
                tmp[0] = (ch.getUInt32() >> 10) + 0xD800;
                tmp[1] = (ch.getUInt32() & 0x3FF) + 0xDC00;
            }

            for (int j = 0; j < length; j++) {
                result.add(((uint8*)tmp)[byteOrder == BIG_ENDIAN_BYTE_ORDER ? j : length - 1 - j]);
            }

            return std::move(result);
        }

        Number CodecUTF16::decodeOne(InputStream<uint8>* in, ByteOrder byteOrder) const {
            Number tmp = (((uintmax) in->read()) << 8) |  in->read();
            if (tmp >= 0xD800 && tmp <= 0xDBFF) {
                tmp -= 0xD800;
                tmp << 10;
                uint16 secondWord = (((uintmax) in->read()) << 8 | in->read());
                if (secondWord < 0xDC00 || secondWord > 0xDFFF) {
                    throw createException2("CodecUTF16", "Wrong UTF-16 format");
                }
                tmp += secondWord - 0xDC00;
                return tmp;
            } else if (tmp >= 0xDC00 && tmp <= 0xDFFF) {
                uintmax firstWord = (((uintmax) in->read()) << 8 | in->read());
                if (firstWord < 0xD800 || firstWord > 0xDBFF) {
                    throw createException2("CodecUTF16", "Wrong UTF-16 format");
                }
                firstWord = firstWord << 10;
                tmp += firstWord;
                return tmp;
            } else {
                return tmp;
            }
        }

        List<uint8> CodecUTF32::encodeOne(Number ch, ByteOrder byteOrder) const {
            List<uint8> result(4);

            if (byteOrder == BIG_ENDIAN_BYTE_ORDER) {
                result.add((ch.getUInt32() >> 24) & 0xFF);
                result.add((ch.getUInt32() >> 16) & 0xFF);
                result.add((ch.getUInt32() >> 8) & 0xFF);
                result.add(ch.getUInt32() & 0xFF);
            } else {
                result.add(ch.getUInt32() & 0xFF);
                result.add((ch.getUInt32() >> 8) & 0xFF);
                result.add((ch.getUInt32() >> 16) & 0xFF);
                result.add((ch.getUInt32() >> 24) & 0xFF);
            }

            return std::move(result);
        }

        Number CodecUTF32::decodeOne(InputStream<uint8>* in, ByteOrder byteOrder) const {
            Number tmp = 0;
            if (byteOrder == BIG_ENDIAN_BYTE_ORDER) {
                tmp += in->read() << 24;
                tmp += in->read() << 16;
                tmp += in->read() << 8;
                tmp += in->read();
            } else {
                tmp += in->read();
                tmp += in->read() << 8;
                tmp += in->read() << 16;
                tmp += in->read() << 24;
            }

            return tmp;
        }

        KNIIT_LIB_DLL_EXPORT_OR_IMPORT const Codec* _ASCII = new CodecASCII();
        KNIIT_LIB_DLL_EXPORT_OR_IMPORT const Codec* _UTF8 = new CodecUTF8();
        KNIIT_LIB_DLL_EXPORT_OR_IMPORT const Codec* _UTF16 = new CodecUTF16();
        KNIIT_LIB_DLL_EXPORT_OR_IMPORT const Codec* _UTF32 = new CodecUTF32();

        const Codec* ASCII() {
            return _ASCII;
        };

        const Codec* UTF8()  {
            return _UTF8;
        }

        const Codec* UTF16()  {
            return _UTF16;
        }

        const Codec* UTF32()  {
            return _UTF32;
        }

    }
};

