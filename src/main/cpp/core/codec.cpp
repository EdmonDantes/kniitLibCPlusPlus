/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include "core/codec.h"

KNIIT_LIB_NAMESPACE {

    List<uint8> Codec::encode(InputStream<Number>* in, ByteOrder byteOrder) const {
        List<uint8> result;
        while (in->canRead()) {
            result.addAll(encodeOne(in->read(), byteOrder));
        }

        return std::move(result);
    }

    List<Number> Codec::decode(InputStream<uint8>* in, ByteOrder byteOrder) const {
        List<Number> result;
        while (in->canRead()) {
            result.add(decodeOne(in, byteOrder));
        }

        return std::move(result);
    }
};

