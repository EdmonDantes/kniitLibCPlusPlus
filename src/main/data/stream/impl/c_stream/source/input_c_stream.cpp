/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */
#include <iostream>
#include "../../../../../core/exception.h"
#include "../input_c_stream.h"

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
        return stream->tellg();
    }

    void InputCStream::position(uintmax position) {
        stream->seekg(position);
    }

    uint8_t InputCStream::read() {
        if (canRead()) {
            return stream->get();
        } else {
            throw createException2("InputCStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
        }
    }

    uint8_t InputCStream::read(uintmax position) {
        if (isOpen()) {
            uintmax lastPosition = this->position();
            this->position(position);
            uint8_t result = read();
            this->position(lastPosition);
            return result;
        } else {
            throw createException2("InputCStream", KNIIT_LIB_ERROR_CAN_NOT_READ);
        }
    }

    void InputCStream::read(uint8_t* pointer, uintmax length) {
        for (uintmax i = 0; i < length; i++) {
            pointer[i] = read();
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

    void InputCStream::read(uint8_t *pointer, uintmax length, uintmax position) {
        uintmax startPosition = this->position();
        this->position(position);
        read(pointer, length);
        this->position(startPosition);
    }
}