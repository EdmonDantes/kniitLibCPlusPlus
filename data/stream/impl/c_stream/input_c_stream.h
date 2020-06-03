/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_INPUT_C_STREAM_H
#define KNIITLIBRARY_INPUT_C_STREAM_H

#include "../../input_stream.h"
#include <istream>

#ifndef KNIIT_LIB_ERROR_CAN_NOT_READ
#define KNIIT_LIB_ERROR_CAN_NOT_READ "Can not read this value"
#endif

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS InputCStream : public InputStream<uint8_t> {
    protected:
        std::istream* stream = nullptr;
        bool needToRemove = false;
    public:
        /**
         * Default constructor.
         */
        InputCStream();

        /**
         * Move constructor.
         */
        InputCStream(InputCStream&& stream);

        /**
         *  Create InputStream from std::istream
         */
        InputCStream(std::istream* stream, bool needToRemove = false);

        ~InputCStream();

        InputCStream& operator=(InputCStream&& stream);

        /**
         * Open stream from c++ stream
         * @param stream
         * @return True, if it success
         */
        bool open(std::istream* stream);
        void close();

        bool isOpen() const;
        bool isClose() const;
        bool canRead() const;



        uintmax position() const;
        void position(uintmax position);

        uint8_t read();
        uint8_t read(uintmax position);
        void read(uint8_t* pointer, uintmax length);
        void read(uint8_t* pointer, uintmax length, uintmax position);
    };

}
#endif //KNIITLIBRARY_INPUT_C_STREAM_H
