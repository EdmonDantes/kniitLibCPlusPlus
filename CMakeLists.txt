cmake_minimum_required(VERSION 3.15)
project(kniitLibrary)

set(CMAKE_CXX_STANDARD 20)



add_library(kniitLibrary SHARED core/core.h core/datatype.h core/source/datatype.cpp core/datatypes.h core/exception.h core/source/exception.cpp core/comparator.h collections/iterator.h collections/list.h collections/set.h data/data_stream.h data/input_stream.h data/source/input_stream.cpp data/reader_input_stream.h core/number.h core/source/number.cpp data/source/reader_input_stream.cpp math/matrix.h data/output_stream.h data/source/output_stream.cpp data/writer_output_stream.h data/source/writer_output_stream.cpp)

add_executable(testLibrary source/library.cpp)
target_link_libraries(testLibrary kniitLibrary)