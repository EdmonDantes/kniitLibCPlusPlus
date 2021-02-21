//
// Created by masa_ on 12.04.2020.
//
#include "core/exception.h"

KNIIT_LIB_NAMESPACE {

    std::string Exception::getMessage(int countTabs) const {
        std::stringstream ss;

        for (int i = 0; i < countTabs; ++i) {
            ss << '\t';
        }

        ss << "Error ";

        if (code > -1) {
            ss << "#" << code << " ";
        }

        ss << "in file '" << fileName << "' on line '" << line << "' in class '" << className << "' in method '" + methodName + "': ";

        if (message.length() > 0) {
            ss << message;
        }

        if (cause != nullptr && cause != 0) {
            ss << '\n' << cause->getMessage(countTabs + 1);
        }


        return ss.str();
    }

    Exception::Exception(intmax code,
        std::string className,
        std::string methodName,
        std::string fileName,
        int lineOfCode,
        std::string message,
        Exception * cause) {       {
            this->code = code;
            this->className = className;
            this->methodName = methodName;
            this->fileName = fileName;
            this->line = lineOfCode;
            this->message = message;
            this->cause = cause;
        }
    }

    Exception::~Exception() noexcept {
        if (cause != nullptr) {
            delete cause;
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
    std::string Exception::getFullMessage() const {
        return getMessage(0);
    }

    Exception * Exception::getCause() {
        return cause;
    }

    const char* Exception::what() const noexcept {
        const std::string& string = getFullMessage();
        char* c_message = new char[string.length() + 1];
        const char* tmp = string.c_str();
        memcpy(c_message, tmp, string.length());
        c_message[string.length()] = 0;
        return c_message;
    }

    std::ostream & operator<<(std::ostream & out, DEFAULT_EXCEPTION_TYPE ex) {
        out << ex->getFullMessage();
        return out;
    }
}
