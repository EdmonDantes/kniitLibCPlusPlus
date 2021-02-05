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

        /**
         * @return Char which decode codec
         */
        Number readChar();

        /**
         * @param length max strings length
         * @param lastChar last char
         * @param addLastChar if true last char will be added to string
         * @return String with length equals <b>length</b> or less and stopped on <b>lastChar</b>
         */
        String readString(uintmax length = 0, Number lastChar = '\n', bool addLastChar = false);

        /**
         * @return Boolean value from input in format (true/false/TRUE/FALSE) or (1/0).
         */
        bool readBoolean();

        /**
         * Read decimal integer or real number (examples: '-554', '-85,25', '96.25')
         * @param delimiter last char which mark numbers end (default: space)
         */
        Number readNumber(Number delimiter=' ');

        /**
         * Read color value from specified format:
         * <ul>
         * <li>rgb(255;12;25)</li>
         * <li>argb(188;255;12;25)</li>
         * <li>rgb(0(,/.)2;0(,/.)3;0(,/.)4)</li>
         * <li>argb(1(,/.)0;0(,/.)2;0(,/.)3;0(,/.)4)</li>
         * <li>#AARRGGBB</li>
         * <li>#RRGGBB</li>
         * <li>#ARGB</li>
         * <li>#RGB</li>
         * </ul>
         * @param delimiter last char which mark hex color end <i>(default: space. Using only in format which start with <b>#</b>)</i>
         * @return ARGB colors number
         */
        Number readColor(Number delimiter = ' ');
        List<uint8_t> readHex();
        List<Number> readList();
        Set<Number> readSet();
        MutableMatrix<Number> readMatrix();
    };
};
#endif //KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
