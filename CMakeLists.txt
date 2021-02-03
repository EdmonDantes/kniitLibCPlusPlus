cmake_minimum_required(VERSION 3.15)
project(kniitLibrary)

set(CMAKE_CXX_STANDARD 20)

if(DEFINED CMAKE_USE_LINUX)
    add_definitions(-DKNIIT_LIB_DISABLE_AUTO_DETECT_OS -DKNIIT_LIB_USE_UNIX)
else(DEFINED CMAKE_USE_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /UMBCS /D_UNICODE /DUNICODE")
endif(DEFINED CMAKE_USE_LINUX)

add_library(kniitLibrary SHARED
        src/main/core/core.h
        src/main/core/exception.h
        src/main/core/source/exception.cpp
        src/main/core/number.h
        src/main/core/comparator.h
        src/main/collections/iterator.h
        src/main/collections/list.h
        src/main/collections/set.h
        src/main/data/stream/data_stream.h
        src/main/data/stream/impl/c_stream/input_c_stream.h
        src/main/data/stream/impl/c_stream/source/input_c_stream.cpp
        src/main/data/reader_input_stream_old.h
        src/main/core/source/number.cpp
        src/main/data/source/reader_input_stream_old.cpp
        src/main/math/matrix.h
        src/main/data/stream/impl/c_stream/output_c_stream.h
        src/main/data/stream/impl/c_stream/source/output_c_stream.cpp
        src/main/data/writer_output_stream_old.h
        src/main/data/source/writer_output_stream_old.cpp
        src/main/window/win_app.h
        src/main/window/frame.h
        src/main/core/status.h
        src/main/core/codec.h
        src/main/core/string.h
        src/main/core/source/string.cpp
        src/main/core/codecs.h
        src/main/core/source/codecs.cpp
        src/main/data/stream/input_stream.h
        src/main/data/stream/output_stream.h
        src/main/data/stream/impl/liststream/input_list_stream.h
        src/main/data/stream/input_output_stream.h
        src/main/data/stream/impl/c_stream/input_output_c_stream.h
        src/main/data/stream/impl/c_stream/source/input_output_c_stream.cpp
        src/main/data/stream/impl/liststream/output_list_stream.h
        src/main/data/stream/impl/liststream/input_output_list_stream.h
        src/main/core/source/codec.cpp
        src/main/data/stream/impl/buffered/buffered_input_stream.h
        src/main/data/stream/impl/buffered/buffered_output_stream.h
        src/main/data/stream/impl/buffered/buffered_stream_core.h
        src/main/data/reader_input_stream.h
        src/main/data/source/reader_input_stream.cpp)



add_executable(testLibrary src/test/source/library.cpp)
target_link_libraries(testLibrary kniitLibrary)

INSTALL(TARGETS kniitLibrary DESTINATION ${CMAKE_INSTALL_PATH}/dll)
INSTALL (
        DIRECTORY ${CMAKE_SOURCE_DIR}/src/main/
        DESTINATION ${CMAKE_INSTALL_PATH}/headers
        FILES_MATCHING PATTERN "*.h*")