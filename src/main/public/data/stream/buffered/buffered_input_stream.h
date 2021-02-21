/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_INPUT_STREAM_H_
#define KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_INPUT_STREAM_H_
#include "buffered_stream_core.h"
#include "../input_stream.h"
#include <algorithm>

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS BufferedInputStream : public InputStream<T> {
     private:
        InputStream<T>* stream = nullptr;
        T* buffer = nullptr;
        uintmax length = 0;
        uintmax size = 0;
        uintmax index = 0;
        bool movePositionToCenter = false;

     protected:
        virtual void init(InputStream<T>* stream, int length, bool movePositionToCenter) {
            if (buffer != nullptr) {
                delete[] buffer;
            }

            this->stream = stream;
            this->buffer = new T[length];
            this->length = length;
            this->movePositionToCenter = movePositionToCenter;

            fillBuffer(0, movePositionToCenter);
        }

        virtual uintmax fillBuffer(uintmax position, bool movePositionToCenter) {
            this->index = 0;
            this->size = 0;

            uintmax startPosition = position - (length / 2);
            stream->position(movePositionToCenter ? (startPosition > position ? 0 : startPosition) : position);

            while (stream->canRead() && size < length) {
                buffer[size++] = std::move(stream->read());
            }

            return startPosition;
        }
     public:
        BufferedInputStream(InputStream<T>* stream, int length, bool movePositionToCenter = false) {
            init(stream, length, movePositionToCenter);
        }

        BufferedInputStream(InputStream<T>* stream, bool movePositionToCenter = false) : BufferedInputStream(stream, KNIIT_LIB_DEFAULT_BUFFER_SIZE, movePositionToCenter) {}

        bool isOpen() const override {
            return stream != nullptr && buffer != nullptr && (index < size || this->stream->isOpen());
        }

        bool isClose() const override {
            return !isOpen();
        }

        void close() override {
            if (buffer != nullptr) {
                buffer = nullptr;
            }
            stream = nullptr;
            index = size = length = 0;
        }

        uintmax position() const override {
            return stream->position() - size + index;
        }

        void position(uintmax position) override {
            if (position >= stream->position() || position < stream->position() - size) {
                fillBuffer(position, movePositionToCenter);
            }

            this->index = size - (stream->position() - position);
        }

        bool canRead() const override {
            return isOpen() && (index < size || this->stream->canRead());
        }

        T read() override {
            if (index < size) {
                return buffer[index++];
            } else {
                uintmax pos = position();
                fillBuffer(pos, movePositionToCenter);
                this->index = size - (stream->position() - pos);
                return buffer[index++];
            }
        }

        T read(uintmax position) override {
            uintmax startPosition = this->position();

            this->position(position);
            T result = read();
            this->position(startPosition);
            return std::move(result);
        }

        void read(T* pointer, uintmax length) override {
            for (int i = 0; i < length; i++) {
                pointer[i] = read();
            }
        }

        void read(T* pointer, uintmax length, uintmax position) override {
            uintmax startPosition = this->position();

            this->position(position);
            read(pointer, length);
            this->position(startPosition);
        }

    };
};
#endif //KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_INPUT_STREAM_H_
