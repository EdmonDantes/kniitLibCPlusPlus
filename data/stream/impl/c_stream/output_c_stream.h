/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_OUTPUT_C_STREAM_H
#define KNIITLIBRARY_OUTPUT_C_STREAM_H

#include <ostream>
#include "../../../../core/core.h"
#include "../../output_stream.h"

#ifndef KNIIT_LIB_ERROR_CAN_NOT_WRITE
    #define KNIIT_LIB_ERROR_CAN_NOT_WRITE "Can not write this value"
#endif

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS OutputCStream : public OutputStream<uint8_t> {
    protected:
        std::ostream* stream = nullptr;
    public:
        OutputCStream();
        OutputCStream(OutputCStream&& stream);
        OutputCStream(std::ostream* stream);
        OutputCStream& operator=(OutputCStream&& stream);

        ~OutputCStream();

        virtual bool open(std::ostream* stream);

        bool canWrite() const override;
        bool isOpen() const override;
        bool isClose() const override;

        void close() override;

        uintmax position() const override;
        void position(uintmax position) override;

        bool write(uint8_t& obj) override;
        bool write(uint8_t& obj, uintmax position) override;
        bool write(uint8_t* obj, uintmax length) override;
        bool write(uint8_t* obj, uintmax length, uintmax position) override;
    };
};
#endif //KNIITLIBRARY_OUTPUT_C_STREAM_H
