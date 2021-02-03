/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
#define KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
#include "../core/codec.h"
#include "../core/codecs.h"
#include "../core/string.h"
#include "../collections/list.h"
#include "../collections/set.h"
#include "../math/matrix.h"
#include "stream/input_stream.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS ReaderInputStream {
     private:
        InputStream<uint8_t>* stream = nullptr;
        const Codec* codec = nullptr;
        ByteOrder byteOrder;
     protected:
        Number read();

        void init(InputStream<uint8_t>* stream, const Codec* codec, ByteOrder byteOrder);
     public:
        ReaderInputStream(InputStream<uint8_t>* stream, const Codec* codec = KNIIT_LIB_DEFAULT_CODEC, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);

        bool canRead();

        Number readChar();
        String readString(uintmax length = 0, Number lastChar = '\n', bool addLastChar = false);

        bool readBoolean();
        Number readNumber(Number delimiter=' ');
        Number readColor();
        List<uint8_t> readHex();
        List<Number> readList();
        Set<Number> readSet();
        MutableMatrix<Number> readMatrix();
    };
};
#endif //KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
