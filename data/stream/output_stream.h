/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_OUTPUT_STREAM_H
#define KNIITLIBRARY_OUTPUT_STREAM_H
#include "../../core/core.h"
#include "data_stream.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS OutputStream : public DataStream {
    public:
        /**
         * @return True, if you can write to this stream
         */
        virtual bool canWrite() const NO_BODY;

        /**
         * @return True, if all data writed to stream
         */
        virtual bool flush() NO_BODY;

        /**
         * Write object to this stream
         * @param obj
         * @return True, if object was written to this stream
         */
        virtual bool write(T& obj) NO_BODY;

        /**
         * Write object to this stream with special position
         * @param obj
         * @param position
         * @return True, if object was written to this stream
         */
        virtual bool write(T& obj, uintmax position) NO_BODY;

        /**
         * Write object's array to this stream
         * @param obj array
         * @param length array's length
         * @return True, if all objects were written to this stream
         */
        virtual bool write(T* obj, uintmax length) NO_BODY;

        /**
         * Write object's array to this stream with
         * @param obj array
         * @param length array's length
         * @param position
         * @return True, if all objects were written to this stream
         */
        virtual bool write(T* obj, uintmax length, uintmax position) NO_BODY;
    };
};
#endif //KNIITLIBRARY_OUTPUT_STREAM_H
