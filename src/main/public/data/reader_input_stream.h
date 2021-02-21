/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
#define KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
#include "core/codec.h"
#include "core/codecs.h"
#include "core/string.h"
#include "collections/list.h"
#include "collections/set.h"
#include "math/matrix.h"
#include "stream/input_stream.h"
#include "delimiter_strategy.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS ReaderInputStream {
     private:
        InputStream<uint8>* stream = nullptr;
        const Codec* codec = nullptr;
        ByteOrder byteOrder;
        uintmax prevPosition = 0;
     protected:
        Number read();
        void unread();

        void init(InputStream<uint8>* stream, const Codec* codec, ByteOrder byteOrder);
        Number hexCharToValue(uintmax startPosition, Number number);
     public:
        ReaderInputStream(InputStream<uint8>* stream, const Codec* codec = KNIIT_LIB_DEFAULT_CODEC, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);

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
        String readString(uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy('\n', true), bool addLastChar = false);

        /**
         * @return Boolean value from input in format (true/false/TRUE/FALSE) or (1/0).
         */
        bool readBoolean();

        /**
         * Read decimal integer or real number (examples: '-554', '-85,25', '96.25')
         * @param delimiter last char which mark numbers end (default: space)
         * @param skipDelimiter If true skip delimiter and stream will stand on next char after delimiter
         * @param throwOnUnknownChar If true throw exception if find not number characters or delimiter.
         */
        Number readNumber(const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ', true), bool throwOnUnknownChar = true);

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
         * @param skipDelimiter If true skip delimiter and stream will stand on next char after delimiter
         * @return ARGB colors number
         */
        Number readColor(const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ', true));

        /**
         * Read string in hex format (example 'HHFB1256')
         * @param length max length of hex. If 0, length will be unlimited (default: 0)
         * @param delimiter last char which mark hex end (default: space)
         * @param skipDelimiter If true skip delimiter and stream will stand on next char after delimiter
         * @return
         */
        List<uint8> readHex(uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ', true));

        /**
         * Read list values from input if format
         * <ul>
         * <li>[12;56;58;12]</li>
         * <li>[12;56;58;12]</li>
         * <li>12;56;58;12</li>
         * <li>12(,/.)6;56;58;12</li>
         * <li></li>
         * </ul>
         * @param length Max length of list. Element which will be above that, will be not read (0 - unlimited)
         * @param delimiterStrategy Strategy for lists end
         * @param numberDelimiter Delimiter between numbers
         * @return
         */
        List<Number> readNumberList(uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ',true), Number numberDelimiter = Number(';'));

        template <typename T>
        List<T> readList(T& (*valueReader)(String&), uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ', true), Number elementDelimiter = Number(';'));

//        template <typename T>
//        List<T> readList(void* valueReader, uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ',true), Number elementDelimiter = Number(';')) {
//            valueReader();
//        }

//        template <typename T>
//        List<T> readList(const T& (*valueReader)(String&), uintmax length = 0, const DelimiterStrategy& delimiterStrategy = DelimiterStrategy(' ',true), Number elementDelimiter = Number(';')) {
//            uintmax startPosition = stream->position();
//
//            List<Number> result = length > 0 ? List<Number>(length) : List<Number>();
//
//            DelimiterStrategy elementStrategy = delimiterStrategy.plus(elementDelimiter, false);
//            bool withBrackets = false;
//            while (canRead() && (length == 0 || result.size() < length)) {
//                Number ch = read();
//                if (ch == '[') {
//                    if (withBrackets || result.size() > 0) {
//                        stream->position(startPosition);
//                        throw createException2("ReaderInputStream", "Wrong list format");
//                    }
//
//                    withBrackets = true;
//                    elementStrategy.add(']');
//                    Number nextCh = read();
//                    unread();
//                    if (nextCh >= '0' && nextCh <= '9') {
//                        try {
//                            const T& tmp = valueReader(readString(0, elementStrategy, true));
//                            result.add(tmp);
//                        }
//                        catch (Exception& e) {
//                            throw createException3("ReaderInputStream",
//                                "Can not parse number",
//                                new Exception(std::move(e)));
//                        }
//                    }
//                } else if (ch == ']') {
//                    if (!withBrackets) {
//                        stream->position(startPosition);
//                        throw createException2("ReaderInputStream", "Wrong list format");
//                    }
//                    if (canRead() && !delimiterStrategy.isSkipDelimiters()) {
//                        if (!delimiterStrategy.hasDelimiter(read())) {
//                            unread();
//                        }
//                    }
//                    break;
//                } else if (delimiterStrategy.hasDelimiter(ch)) {
//                    if (withBrackets) {
//                        stream->position(startPosition);
//                        throw createException2("ReaderInputStream", "Wrong list format. Miss close bracket");
//                    }
//                    if (!delimiterStrategy.isSkipDelimiters()) {
//                        unread();
//                    }
//                    break;
//                } else {
//                    if (!elementStrategy.hasDelimiter(ch)) {
//                        unread();
//                    }
//                    try {
//                        result.add(valueReader(readString(0, elementStrategy, true)));
//                    }
//                    catch (Exception& e) {
//                        stream->position(startPosition);
//                        throw createException3("ReaderInputStream", "Can not parse number", new Exception(std::move(e)));
//                    }
//                }
//            }
//
//            return std::move(result);
//        }

        Set<Number> readSet();
        MutableMatrix<Number> readMatrix();
    };
};
#endif //KNIITLIBRARY_DATA_READER_INPUT_STREAM_H_
