/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_INPUT_OUTPUT_C_STREAM_H
#define KNIITLIBRARY_INPUT_OUTPUT_C_STREAM_H

#include "../../input_output_stream.h"
#include <sstream>

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS InputOutputCStream : public InputOutputStream<uint8_t> {
     private:
        std::iostream* stream = nullptr;

        void init(std::iostream* stream);
     public:
        /**
         * Default constructor.
         */
        InputOutputCStream();

        /**
         * Move constructor.
         */
        InputOutputCStream(InputOutputCStream&& stream);

        /**
         *  Create InputStream from std::istream
         */
        InputOutputCStream(std::iostream* stream);

        ~InputOutputCStream();

        InputOutputCStream& operator=(InputOutputCStream&& stream);

        /**
         * Open stream from c++ stream
         * @param stream
         * @return True, if it success
         */
        bool open(std::iostream* stream);
        virtual void close() override;

        virtual bool isOpen() const override;
        virtual bool isClose() const override;
        virtual uintmax position() const override;
        virtual void position(uintmax position) override;

        bool canRead() const override;
        uint8_t read() override;
        uint8_t read(uintmax position) override;
        void read(uint8_t* pointer, uintmax length) override;
        void read(uint8_t* pointer, uintmax length, uintmax position) override;

        bool canWrite() const override;
        bool flush() override;
        bool write(uint8_t& obj) override;
        bool write(uint8_t& obj, uintmax position) override;
        bool write(uint8_t* obj, uintmax length) override;
        bool write(uint8_t* obj, uintmax length, uintmax position) override;

    };

};
#endif //KNIITLIBRARY_INPUT_OUTPUT_C_STREAM_H
