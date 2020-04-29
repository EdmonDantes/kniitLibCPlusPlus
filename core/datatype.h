/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Class for define main data types
 *
 * If data type is simple, we can parse it from bytes.
 */

#ifndef KNIITLIBRARY_DATATYPE_H
#define KNIITLIBRARY_DATATYPE_H
#include "core.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS DataType {
            private:
            int id;
            bool simple;
            public:
            DataType(int id, bool simple = false);
            DataType(const DataType& type);

            bool operator==(const DataType& type);
            bool isSimple();

    };
}
#endif //KNIITLIBRARY_DATATYPE_H
