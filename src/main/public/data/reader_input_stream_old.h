///*
// *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
// *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
// */
//
//#ifndef KNIITLIBRARY_READER_INPUT_STREAM_H
//#define KNIITLIBRARY_READER_INPUT_STREAM_H
//#include "../data/stream/impl/c_stream/input_c_stream.h"
//#include "../core/number.h"
//#include "../core/string.h"
//#include "../collections/list.h"
//#include "../collections/set.h"
//#include "../math/matrix.h"
//
//#ifndef KNIIT_LIB_ERROR_FORMAT_ERROR
//#define KNIIT_LIB_ERROR_FORMAT_ERROR "Format error"
//#endif
//
//KNIIT_LIB_NAMESPACE {
//
//    KNIIT_LIB_CLASS ReaderInputStream : public InputCStream {
//    protected:
//        bool skip = false;
//    public:
//        ReaderInputStream();
//        ReaderInputStream(ReaderInputStream&& reader);
//        ReaderInputStream(std::string fileName);
//        ReaderInputStream& operator=(ReaderInputStream&& reader);
//
//        bool open(std::string& fileName);
//
//        void setSkip(bool skip);
//
//

//        bool readBoolean(bool caseSensitive = false, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read 32-bits signed integer value from input in normal decimal format ((-)120785614)
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readInt32(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read 32-bits unsigned integer value from input in normal decimal format (120785614)
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readUInt32(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read signed integer value from input in normal decimal format ((-)120785614)
//            Return type will be crop for using minimum bits for value (int32/int64)
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readInt(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read unsigned integer value from input in normal decimal format ((-)120785614)
//            Return type will be crop for using minimum bits for value (uint32/uint64)
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readUInt(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read signed real value from input in normal decimal format ((-)125(,/.)25)
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readFloat(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read signed real value from input in normal decimal format ((-)125(,/.)25)
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readDouble(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read number value from input in normal decimal format ((-)125(,/.)25 / (-)69448468)
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        //FUTURE: add white list of characters
//        Number readNumber(DataType type = DataTypes::NUMBER, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER, bool throwIfNotRead = true);
//
//        /*
//            Read c++ char value from input ('a')
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        char readASCIIChar();
//
//        /*
//            Read unicode char value from input.
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readUnicodeChar(bool utf8 = false, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read char value from input
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Number readChar(bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read string value from input if string < @param(length) or while not read @param(endChar) or while not read eof
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        std::string readASCIIString(uintmax length = 0, bool addEndChar = false, char endChar = '\n', ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read unicode string value from input if string < @param(length) or while not read @param(endChar) or while not read eof
//
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        String readUnicodeString(uintmax length = 0, bool utf8 = false, bool addEndChar = false, Number endChar = '\n', ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//
//        Number readColor(uint8 zeroAlpha = 0, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read hex data from input and conver to byte array in format (0123456789ABCDEF9876543210)
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        List<uint8> readHex(uintmax length = 0, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read point value from input in format
//                example for length = 2
//
//                (12(,/.)1;15(,/.)5)
//                (12;15(,/.)5)
//                (12(,/.)1;15)
//                (12;15)
//
//            If point will use real number return type will be real
//            If lenght less 1, read variable length point
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        List<Number> readPoint(uintmax length = 0, DataType inputType = DataTypes::NUMBER, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read list values from input if format
//                [12;56;58;12]
//                [12;56;58;12]
//                12;56;58;12
//                12(,/.)6;56;58;12
//
//            If list will use real number return type will be real
//
//            List's size may be less then maxLength, but not equals 0
//            If List's size equals 0, throw KNIIT_LIB_ERROR_CAN_NOT_READ
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        List<Number> readNumberList(uintmax maxLength = 0, DataType inputType = DataTypes::NUMBER, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read set values from input if format
//                {12;56;58}
//                {12(,/.)6;56;58}
//                12;56;58
//                12(,/.)6;56;58
//
//            If set will use real number return type will be real
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        Set<Number> readSet(bool skipNotUnique = false, int length = 0, DataType inputType = DataTypes::NUMBER, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        /*
//            Read matrix values from input if format
//
//                FUTURE: in future add read by columns
//                (l/L) - read lines
//                (c/C) - read columns
//                (l/c)/(L/C) - optional
//
//                FUTURE: (l/c)/(L/C)
//                12;56
//                58;12
//
//                FUTURE: (l/c)/(L/C)
//                {12;56}
//                {58;12}
//
//                FUTURE: (l/c)/(L/C)
//                [12;56]
//                [58;12]
//
//                FUTURE: (l/c)/(L/C)
//                12;56
//                {58;12}
//
//                FUTURE: (l/c)/(L/C)
//                {12;56}
//                58;12
//
//                FUTURE: (l/c)/(L/C)
//                12;56
//                [58;12]
//
//                FUTURE: (l/c)/(L/C)
//                [12;56]
//                58;12
//
//                FUTURE: (l/c)/(L/C)
//                {12;56}
//                [58;12]
//
//                FUTURE: (l/c)/(L/C)
//                [12;56]
//                {58;12}
//
//                FUTURE: (l/c)/(L/C)
//                {12;56;58;12}
//                {12(,/.)6;56;58;12}
//                [12;56;58;12]
//                [12;56;58;12]
//                12;56;58;12
//                12(,/.)6;56;58;12
//
//            If set will use real number return type will be real
//
//            If you use other format throw exception KNIIT_LIB_ERROR_FORMAT_ERROR
//            If can`t read throw exception KNIIT_LIB_ERROR_CAN_NOT_READ
//        */
//        MutableMatrix<Number> readMatrix(uintmax lines = 0, uintmax columns = 0, DataType inputType = DataTypes::NUMBER, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        ~ReaderInputStream();
//    };
//}
//#endif //KNIITLIBRARY_READER_INPUT_STREAM_H
