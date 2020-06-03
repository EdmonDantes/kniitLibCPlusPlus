/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_OUTPUT_STREAM_H_
#define KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_OUTPUT_STREAM_H_
#include "buffered_stream_core.h"
#include "../../output_stream.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS BufferedOutputStream : public OutputStream<T> {
     private:
        OutputStream<T>* stream = nullptr;
        T* buffer = nullptr;
        uintmax length = 0;
        uintmax index = 0;
        uintmax lastPosition = 0;

     protected:
        void init(OutputStream<T>* stream, uintmax length) {
            if (this->buffer != nullptr) {
                delete[] this->buffer;
            }

            this->stream = stream;
            this->stream->position(0);

            this->buffer = new T[length];
            this->length = length;
            this->index = 0;
        }
     public:

        BufferedOutputStream(OutputStream<T>* stream, uintmax length = KNIIT_LIB_DEFAULT_BUFFER_SIZE) {
            init(stream, length);
        }

        bool isOpen() const override {
            return stream != nullptr && buffer != nullptr;
        }

        bool isClose() const override {
            return !isOpen();
        }

        bool flush() override ;

        void close() override {
            if (buffer != nullptr) {
                flush();
                delete[] buffer;
            }

            stream = nullptr;
            length = index = 0;
        }

        uintmax position() const override {
            return stream->position() + index;
        }

        void position(uintmax position) override {
            if (position <= lastPosition) {
                flush();
                lastPosition = std::max(stream->position(), lastPosition);

                stream->position(position);
            } else {
                throw createException2("BufferedOutputStream", "Wrong position");
            }
        }

        bool canWrite() const override {
            return isOpen();
        }

        bool write(T& obj) override {
            if (!canWrite()) {
                throw createException2("BufferedOutputStream", "Can not write to this stream");
            }

            if (index >= length) {
                flush();
            }

            buffer[index++] = obj;
            return true;
        }

        bool write(T& obj, uintmax position) override {
            uintmax startPosition = this->position();

            this->position(position);
            bool result = write(obj);
            this->position(startPosition);
            return result;
        }

        bool write(T* obj, uintmax length) override {
            uintmax startPosition = this->position();
            for (int i = 0; i < length; i++) {
                if (!write(obj[length])) {
                    this->position(startPosition);
                    return false;
                }
            }
        }

        bool write(T* obj, uintmax length, uintmax position) override {
            uintmax startPosition = this->position();

            this->position(position);
            bool result = write(obj, length);
            this->position(startPosition);
            return result;
        }
    };

    template <class T>
    bool BufferedOutputStream<T>::flush() {
        if (isClose() || !stream->write(buffer, index)) {
            return false;
        }

        index = 0;
        return true;
    }
};
#endif //KNIITLIBRARY_DATA_STREAM_IMPL_BUFFERED_BUFFERED_OUTPUT_STREAM_H_
