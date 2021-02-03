//
// Created by masa_ on 12.04.2020.
//
#include "../exception.h"

KNIIT_LIB_NAMESPACE {
    Exception::Exception(intmax code, std::string className, std::string methodName, std::string fileName, int lineOfCode, std::string message, Exception * cause) {
        {
            this->code = code;
            this->className = className;
            this->methodName = methodName;
            this->fileName = fileName;
            this->line = lineOfCode;
            this->message = message;
            this->cause = cause;
        }
    }
    Exception::operator const char*() {
        return getFullMessage().c_str();
    }
    intmax Exception::getCode() {
        return code;
    }
    intmax Exception::getLine() {
        return line;
    }
    std::string Exception::getMessage() {
        return message + (cause != nullptr && cause != 0 ? "\n\tCause:\n" + cause->getMessage() : "");
    }
    std::string Exception::getClassName() {
        return className;
    }
    std::string Exception::getMethodName() {
        return methodName;
    }
    std::string Exception::getFullMessage() {
        std::stringstream ss;

        ss << "Error ";

        if (code > -1) {
            ss << "#" << code << " ";
        }

        ss << "in file '" << fileName << "' on line '" << line << "' in class '" << className << "' in method '" + methodName + "':\n";

        if (message.length() > 0) {
            ss << message;
        }


        return ss.str();
    }
    Exception * Exception::getCause() {
        return cause;
    }
    std::ostream & operator<<(std::ostream & out, DEFAULT_EXCEPTION_TYPE ex) {
        out << ex->getFullMessage();
        return out;
    }
}
