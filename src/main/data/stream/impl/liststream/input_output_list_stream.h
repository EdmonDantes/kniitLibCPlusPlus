/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_INPUT_OUTPUT_LIST_STREAM_H_
#define KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_INPUT_OUTPUT_LIST_STREAM_H_
#include "../../input_output_stream.h"
#include "../../../../collections/list.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS InputOutputListStream : public InputOutputStream<T> {
     private:
        List<T>* list = nullptr;
        uintmax index = 0;
        bool needToRemove = true;

        void init(List<T>* list, bool needToRemove) {
            this->list = list;
            this->index = 0;
            this->needToRemove = needToRemove;
        }
     public:

        InputOutputListStream(List<T>* list, bool needToRemove = true) {
            init(list, needToRemove);
        }

        InputOutputListStream() : InputOutputStream<T>(new List<T>()) {}

        InputOutputListStream(InputOutputListStream&& stream) {
            operator=(std::move(stream));
        }

        ~InputOutputListStream() {
            close();
        }

        InputOutputListStream& operator=(InputOutputListStream&& stream) {
            init(stream.list, stream.needToRemove);
            stream.list = nullptr;
            stream.index = 0;
            stream.needToRemove = false;
        }

        bool isOpen() const override {
            return list != nullptr;
        }

        bool isClose() const override {
            return !isOpen();
        }

        void close() override {
            if (list != nullptr && needToRemove) {
                delete list;
            }

            list = nullptr;
            index = 0;
            needToRemove = false;
        }

        uintmax position() const override {
            if (isClose()) {
                throw createException2("InputOutputStream", "This stream is close");
            }

            return index;
        }

        void position(uintmax position) override {
            if (isClose()) {
                throw createException2("InputOutputStream", "This stream is close");
            }

            if (position > list->size()) {
                throw createException2("InputOutputListStream", "Wrong position");
            }

            index = position;
        }

        bool canRead() const override {
            return isOpen() && index < list->size();
        }

        bool canWrite() const override {
            return isOpen() && index <= list->size();
        }

        T read() override {
            if (!canRead()) {
                throw new
                createException2("InputOutputListStream", "Can not read");
            }

            return list->get(index++);
        }

        T read(uintmax position) override {
            if (!canRead()) {
                throw createException2("InputOutputListStream", "Can not read");
            }

            return list->get(position);
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

        bool flush() override {
            return true;
        }

        bool write(T& obj) override {
            if (!canWrite()) {
                return false;
            }

            list->set(obj, index++);
            return true;
        }

        bool write(T& obj, uintmax position) override {
            if (!canWrite()) {
                return false;
            }

            list->set(obj, position);
            return true;
        }

        bool write(T* obj, uintmax length) override {
            uintmax startPosition = this->position();
            bool result = true;
            for (int i = 0; i < length; i++) {
                if (!write(obj[i])) {
                    result = false;
                    break;
                }
            }

            if (!result) {
                this->position(startPosition);
                return false;
            }

            return true;
        }

        bool write(T* obj, uintmax length, uintmax position) override {
            uintmax startPosition = this->position();

            this->position(position);
            bool result = write(obj, length);
            this->position(startPosition);
            return result;
        }
    };
};
#endif //KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_INPUT_OUTPUT_LIST_STREAM_H_
