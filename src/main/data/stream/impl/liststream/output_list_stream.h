/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_OUTPUT_LIST_STREAM_H_
#define KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_OUTPUT_LIST_STREAM_H_
#include "../../output_stream.h"
#include "../../../../collections/list.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS OutputListStream : public OutputStream<T> {
     private:
        List<T>* list = nullptr;
        uintmax index = 0;
        bool needToRemove = true;

        void init(List<T>* list, bool needToRemove) noexcept {
            this->list = list;
            this->index = 0;
            this->needToRemove = needToRemove;
        }
     public:

        OutputListStream(List<T>* list, bool needToRemove = true) {
            init(list, needToRemove);
        }

        OutputListStream() : OutputStream<T>(new List<T>()){}

        OutputListStream(OutputListStream<T>&& stream) {
            operator=(std::move(stream));
        }

        ~OutputListStream(){
            close();
        }

        OutputListStream& operator=(OutputListStream<T>&& stream)  noexcept {
            close();
            init(stream.list, stream.needToRemove);

            stream.list = nullptr;
            stream.index = 0;
            stream.needToRemove = false;
            return *this;
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
            return index;
        }

        void position(uintmax position) override {
            if (position > list->size()) {
                throw createException2("OutputListStream", "Wrong position")
            }

            index = position;
        }

        bool canWrite() const override {
            return isOpen();
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
            if (!canWrite() || position > list->size()) {
                return false;
            }

            list->set(obj, position);
            return true;
        }

        bool write(T* obj, uintmax length) override {
            if (!canWrite()) {
                return false;
            }

            uintmax startPosition = this->position();

            for (int i = 0; i < length; i++) {
                if (!write(obj[i])) {
                    return false;
                }
            }

            list->setSize(startPosition, true);
            index = startPosition;
        }

        bool write(T* obj, uintmax length, uintmax position) override {
            if (!canWrite()) {
                return false;
            }

            uintmax startPosition = this->position();

            this->position(position);
            for (int i = 0; i < length; i++) {
                write(obj);
            }
            this->position(startPosition);
        }
    };
};
#endif //KNIITLIBRARY_DATA_STREAM_IMPL_LISTSTREAM_OUTPUT_LIST_STREAM_H_
