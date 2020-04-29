/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_OUTPUT_STREAM_H
#define KNIITLIBRARY_OUTPUT_STREAM_H

#include <ostream>
#include "../core/core.h"
#include "data_stream.h"

#ifndef KNIIT_LIB_ERROR_CAN_NOT_WRITE
#define KNIIT_LIB_ERROR_CAN_NOT_WRITE "Can not write this value"
#endif

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS OutputStream : public DataStream {
    protected:
        std::ostream* stream = nullptr;
    public:
        OutputStream();
        OutputStream(OutputStream&& stream);
        OutputStream(std::ostream* stream);
        OutputStream& operator=(OutputStream&& stream);

        ~OutputStream();

        bool open(std::ostream* stream);
        void close();

        bool isOpen();
        bool isClose();

        bool canWrite();

        uintmax position();
        void position(uintmax position);

        bool write(uint8_t byte);
        bool write(uint8_t byte, uintmax position);
        bool write(uint8_t* bytes, uintmax length, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);

    };
};
#endif //KNIITLIBRARY_OUTPUT_STREAM_H
