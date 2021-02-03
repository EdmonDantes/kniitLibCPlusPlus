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

#ifndef KNIIT_LIB_EXTERN
    #ifdef KNIIT_LIB_EXTERN_C_PLUS_PLUS
        #define KNIIT_LIB_EXTERN extern "C++"
    #else
        #define KNIIT_LIB_EXTERN extern "C"
    #endif
#endif

#ifndef KNIIT_LIB_DLL_EXPORT
    #ifdef KNIIT_LIB_IMPORT
        #define KNIIT_LIB_DLL_EXPORT __declspec(dllimport)
    #else
        #define KNIIT_LIB_DLL_EXPORT __declspec(dllexport)
    #endif
#endif

#ifndef KNIIT_LIB_API
    #define KNIIT_LIB_API KNIIT_LIB_EXTERN KNIIT_LIB_DLL_EXPORT
#endif

#ifndef KNIIT_LIB_CLASS
    #define KNIIT_LIB_CLASS class KNIIT_LIB_DLL_EXPORT
#endif

#ifndef KNIIT_LIB_NAMESPACE_NAME
    #define KNIIT_LIB_NAMESPACE_NAME kniitLibrary
#endif

#define KNIIT_LIB_NAMESPACE namespace KNIIT_LIB_NAMESPACE_NAME

#ifndef KNIIT_LIB_DISABLE_AUTO_DETECT_OS
    #if defined(_WIN64) || defined(_WIN32) || defined(WIN64) || defined(WIN32)
        #define KNIIT_LIB_USE_WIN
    #else
        //FUTURE: add support for unix systems
        #error Please change this file for your operation system
        //#define KNIIT_LIB_USE_WIN
        //#define KNIIT_LIB_USE_UNIX
    #endif
#endif

#ifndef KNIIT_LIB_DISABLE_AUTO_DETECT_ARCHITECTURE
    #if defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(__itanium__) || defined(_M_IA64) || defined(__aarch64__) || defined(_WIN64)
        #define KNIIT_LIB_USE_X64
    #else
        #define KNIIT_LIB_USE_X32
    #endif
#endif

#ifdef KNIIT_LIB_USE_WIN
    #include <stdint.h>
#else
    //#include <cstdint>
#endif

#ifndef KNIIT_LIB_DISABLE_MAX_TYPES
    #ifdef KNIIT_LIB_USE_X64
        #ifdef KNIIT_LIB_USE_WIN
typedef int64_t intmax;
typedef uint64_t uintmax;
        #else
typedef unsigned char uint8_t;
typedef long long intmax;
typedef unsigned long long uintmax;
        #endif
    #else
        #ifdef KNIIT_LIB_USE_WIN
typedef int32_t intmax;
typedef uint32_t uintmax;
        #else
typedef unsigned char uint8_t;
typedef int intmax;
typedef unsigned int uintmax;
        #endif
    #endif
#endif

#ifndef __FILENAME__
    #ifdef KNIIT_LIB_USE_UNIX
        #define __FILENAME__ (strrch(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #endif
    #ifdef KNIIT_LIB_USE_WIN
        #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #endif
#endif

KNIIT_LIB_NAMESPACE {
    enum ByteOrder {
        LITTLE_ENDIAN,
        BIG_ENDIAN
    };

    #ifdef KNIIT_LIB_DEFAULT_BYTE_ORDER_LITTLE_ENDIAN
        #define DEFAULT_BYTE_ORDER ByteOrder::LITTLE_ENDIAN
    #else
        #define DEFAULT_BYTE_ORDER ByteOrder::BIG_ENDIAN
    #endif
};

#ifndef NO_BODY
    #define NO_BODY = 0
#endif

#endif