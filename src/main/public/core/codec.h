/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_CODEC_H
#define KNIITLIBRARY_CODEC_H
#include "core.h"
#include "number.h"
#include "../collections/list.h"
#include "../data/stream/input_stream.h"
#include "../data/stream/output_stream.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS Codec {
    public:
        virtual List<uint8> encodeOne(Number ch, ByteOrder byteOrder = DEFAULT_BYTE_ORDER) const NO_BODY;
        virtual Number decodeOne(InputStream<uint8>* in, ByteOrder byteOrder = DEFAULT_BYTE_ORDER) const NO_BODY;

        virtual List<uint8> encode(InputStream<Number>* in, ByteOrder byteOrder = DEFAULT_BYTE_ORDER) const;
        virtual List<Number> decode(InputStream<uint8>* in, ByteOrder byteOrder = DEFAULT_BYTE_ORDER) const;
    };
};
#endif //KNIITLIBRARY_CODEC_H
