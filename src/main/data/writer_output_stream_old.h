////
//// Created by masa_ on 28.04.2020.
////
//
//#ifndef KNIITLIBRARY_WRITER_OUTPUT_STREAM_H
//#define KNIITLIBRARY_WRITER_OUTPUT_STREAM_H
//#include "../core/core.h"
//#include "../core/number.h"
//#include "../collections/list.h"
//#include "../collections/set.h"
//#include "../math/matrix.h"
//#include "../stream/impl/c_stream/output_c_stream.h"
//
//KNIIT_LIB_NAMESPACE {
//    KNIIT_LIB_CLASS WriterOutputStream : public OutputCStream {
//    public:
//        WriterOutputStream(std::string fileName, bool append = false);
//        WriterOutputStream(WriterOutputStream&& reader);
//        bool open(std::string& fileName, bool append = false);
//        WriterOutputStream& operator=(WriterOutputStream&& reader);
//
//        bool writeBoolean(bool value, bool isWord = true, bool upperCase = false, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeInt(Number value, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeUInt(Number value, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeNumber(Number value, uint8_t maxCharAfterPoint = 6, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeASCIIChar(char ch);
//
//        bool writeUnicodeChar(Number ch, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeChar(Number ch, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeASCIIString(std::string str);
//
//        bool writeUnicodeString(List<Number>& str, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeString(List<Number>& str, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeString(std::string str, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeColor(Number value, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeHex(List<uint8_t>& value, uintmax length = 0, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writePoint(List<Number>& value, uint8_t maxCharAfterPoint = 6, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeList(List<Number>& value,  uint8_t maxCharAfterPoint = 6, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeSet(Set<Number>& value,  uint8_t maxCharAfterPoint = 6, bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//
//        bool writeMatrix(MutableMatrix<Number>& matrix, uint8_t maxCharAfterPoint = 6,  bool unicode = false, bool utf8 = true, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);
//    };
//};
//#endif //KNIITLIBRARY_WRITER_OUTPUT_STREAM_H
