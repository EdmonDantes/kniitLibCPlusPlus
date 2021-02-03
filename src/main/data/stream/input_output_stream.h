/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_INPUT_OUTPUT_STREAM_H
#define KNIITLIBRARY_INPUT_OUTPUT_STREAM_H
#include "input_stream.h"
#include "output_stream.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS InputOutputStream : public InputStream<T>, public OutputStream<T> {

    };
};
#endif //KNIITLIBRARY_INPUT_OUTPUT_STREAM_H
