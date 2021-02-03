/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_INPUT_STREAM_H
#define KNIITLIBRARY_INPUT_STREAM_H
#include "../../core/core.h"
#include "data_stream.h"

KNIIT_LIB_NAMESPACE {
    /**
     * Interface for income data streams
     * @tparam T
     */
    template <class T>
    KNIIT_LIB_CLASS InputStream : public DataStream {
    public:

        /**
         * @return True, if you can read from this stream.
         */
        virtual bool canRead() const NO_BODY;

        /**
         * Read object from stream
         * @return Object from current position in stream
         */
        virtual T read() NO_BODY;

        /**
         * Read object from stream
         * @param position
         * @return Object from special position in stream
         */
        virtual T read(uintmax position) NO_BODY;

        /**
         * Read objects from stream from current position with special length
         * @param pointer
         * @param length
         * @param byteOrder
         */
        virtual void read(T* pointer, uintmax length) NO_BODY;

        /**
         * Read objects from stream from special position with special length
         * @param pointer
         * @param length
         * @param byteOrder
         */
        virtual void read(T* pointer, uintmax length, uintmax position) NO_BODY;
    };
};
#endif //KNIITLIBRARY_INPUT_STREAM_H
