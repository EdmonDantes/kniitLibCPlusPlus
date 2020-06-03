/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
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

};

