/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Namespace for different main data types.
 */

#ifndef KNIITLIBRARY_DATATYPES_H
#define KNIITLIBRARY_DATATYPES_H
#include "datatype.h"

KNIIT_LIB_NAMESPACE {
    namespace DataTypes {
#ifndef KNIIT_LIB_DATA_TYPES
#define KNIIT_LIB_DATA_TYPES
        /*Simple Type*/
        KNIIT_LIB_DLL_EXPORT const DataType BOOLEAN(0, true);
        KNIIT_LIB_DLL_EXPORT const DataType INT32(1, true);
        KNIIT_LIB_DLL_EXPORT const DataType UINT32(2, true);
        KNIIT_LIB_DLL_EXPORT const DataType INT(3, true);
        KNIIT_LIB_DLL_EXPORT const DataType UINT(4, true);
        KNIIT_LIB_DLL_EXPORT const DataType FLOAT(5, true);
        KNIIT_LIB_DLL_EXPORT const DataType DOUBLE(6, true);
        KNIIT_LIB_DLL_EXPORT const DataType NUMBER(7, true);
        KNIIT_LIB_DLL_EXPORT const DataType CHAR(8, true);
        KNIIT_LIB_DLL_EXPORT const DataType UNICODE_CHAR(9, true);

#ifdef KNIIT_LIB_USE_X64
        KNIIT_LIB_DLL_EXPORT const DataType INT64(10, true);
		KNIIT_LIB_DLL_EXPORT const DataType UINT64(11, true);
#endif // KNIIT_LIB_USE_X64

        // WIP
        // KNIIT_LIB_DLL_EXPORT const DataType LONG_NUMBER		(12, true)

        /*Complex Type*/
        KNIIT_LIB_DLL_EXPORT const DataType STRING(20, false);
        KNIIT_LIB_DLL_EXPORT const DataType UNICODE_STRING(21, false);
        KNIIT_LIB_DLL_EXPORT const DataType COLOR(22, false);
        KNIIT_LIB_DLL_EXPORT const DataType HEX(23, false);
        KNIIT_LIB_DLL_EXPORT const DataType POINT(24, false);
        KNIIT_LIB_DLL_EXPORT const DataType LIST(25, false);
        KNIIT_LIB_DLL_EXPORT const DataType SET(26, false);
        KNIIT_LIB_DLL_EXPORT const DataType MATRIX(27, false);

        // WIP
        //KNIIT_LIB_DLL_EXPORT const DataType TREE				(28, false);

#endif
    }
}

#endif //KNIITLIBRARY_DATATYPES_H
