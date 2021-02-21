/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_INPUT_LIST_STREAM_H
#define KNIITLIBRARY_INPUT_LIST_STREAM_H
#include "../input_stream.h"
#include "collections/list.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS InputListStream : public InputStream<T> {
     private:
        const List<T>* list = nullptr;
        uintmax index = 0;
        bool needToRemove = true;

        void init(const List<T>* list, bool needToRemove) {
            this->list = list;
            this->index = 0;
            this->needToRemove = needToRemove;
        }

     public:
        InputListStream(const List<T>* list, bool needToRemove = true) {
            init(list, needToRemove);
        }

        InputListStream() : InputStream<T>(new List<T>()) {
        }

        InputListStream(InputListStream<T>&& stream) {
            operator=(std::move(stream));
        }

        ~InputListStream() {
            close();
        }

        InputListStream& operator=(InputListStream&& stream) noexcept {
            close();
            init(stream.list, stream.needToRemove);

            this->index = stream.index = 0;
            stream.list = nullptr;
            stream.needToRemove = false;

            return *this;
        }

        bool canRead() const override {
            return this->list != nullptr && index < list->size();
        }

        bool isOpen() const override {
            return list != nullptr;
        }

        bool isClose() const override {
            return list == nullptr;
        }

        void close() override {
            if (list != nullptr && needToRemove) {
                delete list;
            }

            list = nullptr;
            needToRemove = false;
        }

        uintmax position() const override {
            return index;
        }

        void position(uintmax position) override {
            if (position < list->size()) {
                this->index = position;
            } else {
                throw createException2("InputListStream", "Can not set position to: " + position);
            }
        }

        T read() override {
            if (!canRead()) {
                throw createException2("InputListStream", "Can not read value from this stream");
            }

            return ((List<T>*) list) -> get(index++);
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

        List<T>* getList() {
            return list;
        }

    };
};
#endif //KNIITLIBRARY_INPUT_LIST_STREAM_H
