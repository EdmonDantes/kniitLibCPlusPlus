/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_DATA_STREAM_H
#define KNIITLIBRARY_DATA_STREAM_H
#include "core/core.h"

KNIIT_LIB_NAMESPACE {

    /**
     * Interface for all streams
     */
    KNIIT_LIB_CLASS DataStream {
    public:
        /**
         * @return True, if stream if open
         */
        virtual bool isOpen() const NO_BODY;

        /**
         * @return True, if stream if close
         */
        virtual bool isClose() const NO_BODY;

        /**
         * Close this stream.
         * If it closed, do nothing.
         */
        virtual void close() NO_BODY;

        /**
         * @return current position in this stream
         */
        virtual uintmax position() const NO_BODY;

        /**
         * Set current position in this stream
         * @param position
         */
        virtual void position(uintmax position) NO_BODY;
    };
}
#endif //KNIITLIBRARY_DATA_STREAM_H
