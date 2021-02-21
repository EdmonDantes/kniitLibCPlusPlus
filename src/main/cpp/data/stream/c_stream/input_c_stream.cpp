/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */
#include <iostream>
#include "core/exception.h"
#include "data/stream/c_stream/input_c_stream.h"

KNIIT_LIB_NAMESPACE {
    InputCStream::InputCStream(std::istream * stream, bool needToRemove) {
        open(stream);
        this->needToRemove = needToRemove;
    }

    InputCStream::~InputCStream() {
        close();
    }

    bool InputCStream::open(std::istream* stream) {
        close();

        if (stream != nullptr && stream->good() && !stream->eof()) {
            this->stream = stream;
            return true;
        }
        return false;
    }

    void InputCStream::close() {
        if (isOpen() && needToRemove) {
            delete stream;
        }
        stream = nullptr;
    }

    bool InputCStream::isOpen() const {
        return stream != nullptr;
    }

    bool InputCStream::isClose() const {
        return !isOpen();
    }

    bool InputCStream::canRead() const {
        if (isOpen() && stream->good()) {
            stream->get();
            bool isEOF = stream->eof();
            stream->unget();
            return !isEOF;
        }
        return false;
    }

    uintmax InputCStream::position() const {
        if (isOpen()) {
            return stream->tellg();
        } else {
            throw createException2("InputCStream", "Stream is not open");
        }
    }

    void InputCStream::position(uintmax position) {
        if (isOpen()) {
            stream->seekg(position);
        } else {
            throw createException2("InputCStream", "Stream is not open");
        }
    }

    uint8 InputCStream::read() {
        if (canRead()) {
            return stream->get();
        } else {
            throw createException2("InputCStream", "Can not read cstream");
        }
    }

    uint8 InputCStream::read(uintmax position) {
        if (isOpen()) {
            uintmax lastPosition = this->position();
            this->position(position);
            uint8 result = read();
            this->position(lastPosition);
            return result;
        } else {
            throw createException2("InputCStream", "Can not read cstream");
        }
    }

    void InputCStream::read(uint8* pointer, uintmax length) {
        uintmax i = 0;
        for (; i < length && canRead(); i++) {
            pointer[i] = read();
        }

        if (i < length) {
            throw createException2("InputCStream", "Can not read too much bytes");
        }
    }

    InputCStream::InputCStream() {}

    InputCStream::InputCStream(InputCStream &&stream) {
        operator=(std::move(stream));
    }

    InputCStream &InputCStream::operator=(InputCStream&& stream) {
        if (this->stream != nullptr) {
            delete this->stream;
        }

        this->stream = stream.stream;
        stream.stream = nullptr;
        return *this;
    }

    void InputCStream::read(uint8 *pointer, uintmax length, uintmax position) {
        uintmax startPosition = this->position();
        this->position(position);
        read(pointer, length);
        this->position(startPosition);
    }
}