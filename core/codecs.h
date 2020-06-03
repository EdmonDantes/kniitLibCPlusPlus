/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_CODECS_H
#define KNIITLIBRARY_CODECS_H
#include "codec.h"

KNIIT_LIB_NAMESPACE {



    namespace Codecs {

        KNIIT_LIB_CLASS CodecASCII : public Codec {
         public:
            List<uint8_t> encodeOne(Number ch, ByteOrder byteOrder) const override;
            Number decodeOne(InputStream<uint8_t>* in, ByteOrder byteOrder) const override;
        };

        KNIIT_LIB_CLASS CodecUTF8 : public Codec {
         public:
            List<uint8_t> encodeOne(Number ch, ByteOrder byteOrder) const override;
            Number decodeOne(InputStream<uint8_t>* in, ByteOrder byteOrder) const override;
        };

        KNIIT_LIB_CLASS CodecUTF16 : public Codec {
         public:
            List<uint8_t> encodeOne(Number ch, ByteOrder byteOrder) const override;
            Number decodeOne(InputStream<uint8_t>* in, ByteOrder byteOrder) const override;
        };

        KNIIT_LIB_CLASS CodecUTF32 : public Codec {
         public:
            List<uint8_t> encodeOne(Number ch, ByteOrder byteOrder) const override;
            Number decodeOne(InputStream<uint8_t>* in, ByteOrder byteOrder) const override;
        };

        KNIIT_LIB_API const Codec* ASCII();
        KNIIT_LIB_API const Codec* UTF8();
        KNIIT_LIB_API const Codec* UTF16();
        KNIIT_LIB_API const Codec* UTF32();

        #ifndef KNIIT_LIB_DEFAULT_CODEC
        #define KNIIT_LIB_DEFAULT_CODEC KNIIT_LIB_NAMESPACE_NAME::Codecs::ASCII()
        #endif
    }
};
#endif //KNIITLIBRARY_CODECS_H
