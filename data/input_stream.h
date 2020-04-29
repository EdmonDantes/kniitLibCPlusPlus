/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_INPUT_STREAM_H
#define KNIITLIBRARY_INPUT_STREAM_H

#include "../core/core.h"
#include "data_stream.h"
#include <istream>

#ifndef KNIIT_LIB_ERROR_CAN_NOT_READ
#define KNIIT_LIB_ERROR_CAN_NOT_READ "Can not read this value"
#endif

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS InputStream : public DataStream {
    protected:
        std::istream* stream = nullptr;
    public:
        /**
         * Default constructor.
         */
        InputStream();

        /**
         * Move constructor.
         */
        InputStream(InputStream&& stream);

        /**
         *  Create InputStream from std::istream
         */
        InputStream(std::istream* stream);

        ~InputStream();

        InputStream& operator=(InputStream&& stream);

        //FUTURE: change description
        /*
            Open InputStream from std::istream
        */
        bool open(std::istream* stream);
        void close();

        bool isOpen();
        bool isClose();

        //FUTURE: change description
        /*
            Return true if you can read one byte from InputStream
        */
        bool canRead();

        uintmax position();
        void position(uintmax position);

        //FUTURE: change description
        /*
            Read one byte from input.

            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
        */
        uint8_t read();

        //FUTURE: change description
        /*
            Read one byte from special position.

            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
        */
        uint8_t read(uintmax position);

        //FUTURE: change description
        /*
            Read some bytes from input

            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
        */
        void read(uint8_t* pointer, uintmax length, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
    };

}
#endif //KNIITLIBRARY_INPUT_STREAM_H
