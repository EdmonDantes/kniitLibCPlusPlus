cmake_minimum_required(VERSION 3.15)
project(kniitLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(kniitLibrary SHARED core/core.h core/exception.h core/source/exception.cpp core/comparator.h collections/iterator.h collections/list.h collections/set.h data/stream/data_stream.h data/stream/impl/c_stream/input_c_stream.h data/stream/impl/c_stream/source/input_c_stream.cpp data/reader_input_stream_old.h core/number.h core/source/number.cpp data/source/reader_input_stream_old.cpp math/matrix.h data/stream/impl/c_stream/output_c_stream.h data/stream/impl/c_stream/source/output_c_stream.cpp data/writer_output_stream_old.h data/source/writer_output_stream_old.cpp window/win_app.h window/frame.h core/status.h core/codec.h core/string.h core/source/string.cpp core/codecs.h core/source/codecs.cpp data/stream/input_stream.h data/stream/output_stream.h data/stream/impl/liststream/input_list_stream.h data/stream/input_output_stream.h data/stream/impl/c_stream/input_output_c_stream.h data/stream/impl/c_stream/source/input_output_c_stream.cpp data/stream/impl/liststream/output_list_stream.h data/stream/impl/liststream/input_output_list_stream.h core/source/codec.cpp data/stream/impl/buffered/buffered_input_stream.h data/stream/impl/buffered/buffered_output_stream.h data/stream/impl/buffered/buffered_stream_core.h data/reader_input_stream.h data/source/reader_input_stream.cpp)

add_executable(testLibrary source/library.cpp)
target_link_libraries(testLibrary kniitLibrary)