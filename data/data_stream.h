/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_DATA_STREAM_H
#define KNIITLIBRARY_DATA_STREAM_H
#include "../core/core.h"

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS DataStream {
    public:
        /**
         * * //FUTURE: change
            Return true if DataStream is open
        */
        virtual bool isOpen() = 0;

        /**
         * //FUTURE: change
            Return true if DataStream is close
        */
        virtual bool isClose() = 0;

        /**
            Close DataStream
        */
        virtual void close() = 0;

        /**
         * * //FUTURE: change
            Get position in DataStream
        */
        virtual uintmax position() = 0;

        /**
            Set position for DataStream
        */
        virtual void position(uintmax position) = 0;
    };
}
#endif //KNIITLIBRARY_DATA_STREAM_H
