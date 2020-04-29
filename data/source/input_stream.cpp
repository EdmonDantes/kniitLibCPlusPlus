/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */
#include "../input_stream.h"
#include "../../core/exception.h"

KNIIT_LIB_NAMESPACE {
    InputStream::InputStream(std::istream * stream) {
        open(stream);
    }

    InputStream::~InputStream() {
        close();
    }

    bool InputStream::open(std::istream* stream) {
        if (stream != nullptr && stream->good() && !stream->eof()) {
            this->stream = stream;
            return true;
        }
        return false;
    }

    void InputStream::close() {
        if (isOpen()) {
            delete stream;
        }
        stream = nullptr;
    }

    bool InputStream::isOpen() {
        return stream != nullptr;
    }

    bool InputStream::isClose() {
        return !isOpen();
    }

    bool InputStream::canRead() {
        if (isOpen() && stream->good()) {
            stream->get();
            bool isEOF = stream->eof();
            stream->unget();
            return !isEOF;
        }
        return false;
    }

    uintmax InputStream::position() {
        return stream->tellg();
    }

    void InputStream::position(uintmax position) {
        stream->seekg(position);
    }

    uint8_t InputStream::read() {
        if (canRead()) {
            return stream->get();
        } else {
            throw createException2("InputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
        }
    }

    uint8_t InputStream::read(uintmax position) {
        if (isOpen()) {
            uintmax lastPosition = this->position();
            this->position(position);
            uint8_t result = read();
            this->position(lastPosition);
            return result;
        } else {
            throw createException2("InputStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
        }
    }

    void InputStream::read(uint8_t* pointer, uintmax length, ByteOrder byteOrder) {
        for (uintmax i = 0; i < length; i++) {
            pointer[byteOrder == LITTLE_ENDIAN ? length - i - 1 : i] = read();
        }
    }

    InputStream::InputStream() {}

    InputStream::InputStream(InputStream &&stream) {
        operator=(std::move(stream));
    }

    InputStream &InputStream::operator=(InputStream&& stream) {
        if (this->stream != nullptr) {
            delete this->stream;
        }

        this->stream = stream.stream;
        stream.stream = nullptr;
        return *this;
    }
}