/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Core parameters:
 * #define KNIIT_LIB_EXTERN_C_PLUS_PLUS - 'extern "C"' will be replace to 'extern "C++"'
 * #define KNIIT_LIB_IMPORT - use 'dllimport' instead 'dllexport'
 * #define KNIIT_LIB_DISABLE_AUTO_DETECT_OS - disable auto detect operation system. You must add '#define KNIIT_LIB_USE_WIN' or '#define KNIIT_LIB_USE_UNIX'
 * #define KNIIT_LIB_DISABLE_AUTO_DETECT_ARCHITECTURE - disable auto detect computer's architecture. You must add '#define KNIIT_LIB_USE_X64' or '#define KNIIT_LIB_USE_X32'
 * #define KNIIT_LIB_DISABLE_MAX_TYPES - remove library max types (like uintmax and intmax).
 * #define KNIIT_LIB_DEFAULT_BYTE_ORDER_LITTLE_ENDIAN - use little endian like default byte order.
 *
 * Core required parameters:
 * #define NO_BODY - add after method in classes without body
 */

#ifndef KNIITLIBRARY_CORE_H
#define KNIITLIBRARY_CORE_H

//  Support defines
//      KNIIT_LIB_USE_X16
//      KNIIT_LIB_USE_X32
//      KNIIT_LIB_USE_X64
#ifndef KNIIT_LIB_DISABLE_AUTO_DETECT_ARCHITECTURE
    #if defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(__itanium__) || defined(_M_IA64) || defined(__aarch64__) || defined(_WIN64)
        #define KNIIT_LIB_USE_X64
    #else
        #define KNIIT_LIB_USE_X32
    #endif
#endif

//  Support defines
//      KNIIT_LIB_USE_WIN
//      KNIIT_LIB_USE_UNIX
//  Required defines
//      KNIIT_LIB_DLL_EXPORT_OR_IMPORT
#ifndef KNIIT_LIB_DISABLE_AUTO_DETECT_OS
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__CYGWIN__)
        #define KNIIT_LIB_USE_WIN
        #ifndef KNIIT_LIB_DLL_EXPORT_OR_IMPORT
            #ifdef KNIIT_LIB_IMPORT
                #define KNIIT_LIB_DLL_EXPORT_OR_IMPORT __declspec(dllimport)
            #else
                #define KNIIT_LIB_DLL_EXPORT_OR_IMPORT __declspec(dllexport)
            #endif
        #endif
    #else
        #if defined(__GNUC__) && __GNUC__ >= 4
            #define KNIIT_LIB_USE_UNIX
            #ifndef KNIIT_LIB_DLL_EXPORT_OR_IMPORT
                #define KNIIT_LIB_DLL_EXPORT_OR_IMPORT __attribute__ ((visibility("default")))
            #endif
        #else
            #error Unknown operation system. Please use define KNIIT_LIB_DISABLE_AUTO_DETECT_OS
            #ifndef KNIIT_LIB_DLL_EXPORT_OR_IMPORT
                #define KNIIT_LIB_DLL_EXPORT_OR_IMPORT
            #endif
        #endif
    #endif
#endif

#ifdef KNIIT_LIB_USE_WIN
    #define _GLIBCXX_TXN_SAFE_DYN
    #define _GLIBCXX_NOTHROW noexcept
#endif

#ifndef KNIIT_LIB_EXTERN
    #define KNIIT_LIB_EXTERN extern "C"
#endif

#ifndef KNIIT_LIB_API
    #define KNIIT_LIB_API KNIIT_LIB_EXTERN KNIIT_LIB_DLL_EXPORT_OR_IMPORT
#endif

#ifndef KNIIT_LIB_CLASS
    #define KNIIT_LIB_CLASS class KNIIT_LIB_DLL_EXPORT_OR_IMPORT
#endif

#ifndef KNIIT_LIB_NAMESPACE_NAME
    #define KNIIT_LIB_NAMESPACE_NAME kniit_library
#endif

#define KNIIT_LIB_NAMESPACE namespace KNIIT_LIB_NAMESPACE_NAME


#ifndef KNIIT_LIB_DISABLE_LIB_TYPES
    #ifdef KNIIT_LIB_USE_X16
typedef unsigned short uintmax;
typedef short uintmax;

typedef unsigned short uint16;
typedef short int16;

typedef unsigned char uint8;
typedef char int8;
    #elif defined(KNIIT_LIB_USE_X32)
typedef unsigned int uintmax;
typedef int intmax;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned short uint16;
typedef short int16;

typedef unsigned char uint8;
typedef char int8;
    #elif defined(KNIIT_LIB_USE_X64)
typedef unsigned long long uintmax;
typedef long long intmax;

typedef unsigned long long uint64;
typedef long long int64;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned short uint16;
typedef short int16;

typedef unsigned char uint8;
typedef char int8;
    #else
        #error You did not set architecture. Please set one or use define KNIIT_LIB_DISABLE_LIB_TYPES
    #endif
#endif


#ifndef __FILENAME__
    #include <cstring>

    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

KNIIT_LIB_NAMESPACE {
    enum ByteOrder {
        LITTLE_ENDIAN_BYTE_ORDER,
        BIG_ENDIAN_BYTE_ORDER
    };

    #ifdef KNIIT_LIB_DEFAULT_BYTE_ORDER_LITTLE_ENDIAN
        #define DEFAULT_BYTE_ORDER KNIIT_LIB_NAMESPACE_NAME::ByteOrder::LITTLE_ENDIAN_BYTE_ORDER
    #else
        #define DEFAULT_BYTE_ORDER KNIIT_LIB_NAMESPACE_NAME::ByteOrder::BIG_ENDIAN_BYTE_ORDER
    #endif
};

#ifndef NO_BODY
    #define NO_BODY = 0
#endif

#endif