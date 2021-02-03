/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * All classes in library throw pointer to object of this class.
 *
 * Have many information about error.
 *
 * You can create exception with macro's createException4, createException3, createException2.
 */

#ifndef KNIITLIBRARY_EXCEPTION_H
#define KNIITLIBRARY_EXCEPTION_H

#include "core.h"
#include <string>
#include <sstream>

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS Exception : std::exception {
            private:
            intmax code;
            intmax line;
            std::string className;
            std::string methodName;
            std::string fileName;
            std::string message;
            Exception* cause;
            public:
            Exception(intmax code, std::string className, std::string methodName, std::string fileName, int lineOfCode, std::string message, Exception* cause);

            operator const char* ();
            intmax getCode();
            intmax getLine();
            std::string getMessage();
            std::string getClassName();
            std::string getMethodName();
            std::string getFullMessage();
            Exception* getCause();
    };


    #define getFunctionName() __func__
    #define getFileName() __FILENAME__
    #define getLineOfCode() __LINE__
    #define DEFAULT_EXCEPTION_TYPE Exception*
    #define createException4(code, className, message, cause) new Exception((code), (className), getFunctionName(), getFileName(), getLineOfCode(), (message), (cause))
    #define createException3(className, message, cause) createException4(-1, (className), (message), (cause))
    #define createException2(className, message) createException3((className), (message), nullptr)

    KNIIT_LIB_DLL_EXPORT std::ostream& operator <<(std::ostream& out, DEFAULT_EXCEPTION_TYPE ex);

}

#endif //KNIITLIBRARY_EXCEPTION_H
