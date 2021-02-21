/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include <locale>
#include "core/string.h"
#include "data/stream/liststream/input_list_stream.h"

KNIIT_LIB_NAMESPACE {

    String::String(uintmax countOfChar) {
        value = new List<Number>(countOfChar);
    }

    void String::addChar(Number ch) {
        if (value == nullptr) {
            value = new List<Number>();
        }

        value->add(ch);
    }

    String::String() {}

    String::String(const char &ch) {
        addChar(ch);
    }

    String::String(const wchar_t &wch) {
        addChar(wch);
    }

    String::String(const char *str) {
        char* position = const_cast<char*>(str);

        while ((*position) != 0) {
            addChar(*position);
            position++;
        }
    }

    String::String(const wchar_t *wstr) {
        wchar_t* position = const_cast<wchar_t*>(wstr);

        while ((*position) != 0) {
            addChar(*(position++));
        }
    }

    String::String(const char* str, uintmax size) {
        for (int i = 0; i < size; ++i) {
            addChar(str[i]);
        }
    }

    String::String(const wchar_t* str, uintmax size) {
        for (int i = 0; i < size; ++i) {
            addChar(str[i]);
        }
    }

    String::String(const std::string &str) : String(str.c_str()) {}

    String::String(const std::wstring &wstr) : String(wstr.c_str()) {}

    String::String(List<uint8>& bytes, const Codec *codec, ByteOrder byteOrder) {
        if (this->value != nullptr) {
            delete[] this->value;
        }

        InputListStream<uint8> in(&bytes, false);
        this->value = new List<Number>(std::move(codec->decode(&in, byteOrder)));
    }

    String::String(const String &str) {
        if (this->value != nullptr) {
            this->value->clear();
        }

        for (int i = 0; i < str.size(); i++) {
            addChar(str.charAt(i));
        }
    }

    String::String(String &&String) {
        if (this->value != nullptr) {
            delete this->value;
        }

        this->value = String.value;
        String.value = nullptr;
    }

    String::~String() {
        if (this->value != nullptr) {
            delete this->value;
        }
    }

    uintmax String::size() const {
        return this->value == nullptr ? 0 : this->value->size();
    }

    bool String::isEmpty() const {
        return size() <= 0;
    }

    const Number& String::charAt(uintmax index) const {
        if (index < size()) {
            return (*this->value)[index];
        } else {
            throw createException2("String", "Wrong index");
        }
    }

    String String::substring(uintmax startIndex) const {
        return std::move(substring(startIndex, size()));
    }

    String String::substring(uintmax startIndex, uintmax endIndex) const {
        if (isEmpty()) {
            throw createException2("String", "String is empty");
        }
        String result;
        for (int i = startIndex; i < endIndex; i++) {
            result.addChar(charAt(i));
        }
        return std::move(result);
    }

    String String::reverse() const {
        String result;
        result.value = new List<Number>(std::move(this->value->reverse()));
        return std::move(result);
    }

    std::string String::toString() const {
        if (isEmpty()) {
            return "";
        }

        std::stringstream ss;
        for (int i = 0; i < size(); i++) {
            ss << charAt(i).getInt8();
        }
        return ss.str();
    }

    std::wstring String::toWString() const {
        if (isEmpty()) {
            return L"";
        }

        std::wstringstream ss;
        for (int i = 0; i < size(); i++) {
#ifdef KNIIT_LIB_USE_WIN
            ss << charAt(i).getInt16();
#else
            ss << (*this->value)[i].getInt32();
#endif
        }
        return ss.str();
    }

    List<uint8> String::to(const Codec *codec, bool addZeroToEnd, ByteOrder byteOrder) const {
        InputListStream<Number> in(this->value, false);
        List<uint8> result = codec->encode(&in, byteOrder);
        if (addZeroToEnd) {
            result.addAll(codec->encodeOne(0, byteOrder));
        }
        return std::move(result);
    }

    String &String::operator=(String str) {
        if (this->value != nullptr) {
            this->value->clear();
        }

        for (int i = 0; i < str.size(); i++) {
            addChar(str.charAt(i));
        }

        return *this;
    }

    String &String::operator=(Number unicodeChar) {
        if (this->value != nullptr) {
            delete this->value;
        }

        addChar(unicodeChar);
        return *this;
    }

    String &String::operator=(const char &ch) {
        return operator=(Number(ch));
    }

    String &String::operator=(const wchar_t &wch) {
        return operator=(Number(wch));
    }

    String &String::operator=(const char *str) {
        return operator=(String(str));
    }

    String &String::operator=(const wchar_t *wstr) {
        return operator=(String(wstr));
    }

    String &String::operator=(const std::string &str) {
        return operator=(String(str));
    }

    String &String::operator=(const std::wstring &wstr) {
        return operator=(String(wstr));
    }

    String String::operator+(String str) const {
        String result;
        for (int i = 0; i < size(); i++) {
            result.addChar(charAt(i));
        }

        for (int i = 0; i < str.size(); i++) {
            result.addChar(str.charAt(i));
        }

        return std::move(result);
    }

    String String::operator+(Number unicodeChar) const {
        String result;
        for (int i = 0; i < size(); i++) {
            result.addChar(charAt(i));
        }

        result.addChar(unicodeChar);

        return std::move(result);
    }

    String String::operator+(const char &ch) const {
        return std::move(operator+(Number(ch)));
    }

    String String::operator+(const wchar_t &wch) const {
        return std::move(operator+(Number(wch)));
    }

    String String::operator+(const char *str) const {
        return std::move(operator+(String(str)));
    }

    String String::operator+(const wchar_t *wstr) const {
        return std::move(operator+(String(wstr)));
    }

    String String::operator+(const std::string &str) const {
        return std::move(operator+(String(str)));
    }

    String String::operator+(const std::wstring &wstr) const {
        return std::move(operator+(String(wstr)));
    }

    String& String::operator+=(String str) {
        for (int i = 0; i < str.size(); i++) {
            addChar(str.charAt(i));
        }
        return *this;
    }

    String &String::operator+=(Number unicodeChar) {
        addChar(unicodeChar);
        return *this;
    }

    String &String::operator+=(const char &ch) {
        return operator=(Number(ch));
    }

    String &String::operator+=(const wchar_t &wch) {
        return operator=(Number(wch));
    }

    String &String::operator+=(const char *str) {
        return operator+=(String(str));
    }

    String &String::operator+=(const wchar_t *wstr) {
        return operator+=(String(wstr));
    }

    String &String::operator+=(const std::string &str) {
        return operator+=(String(str));
    }

    String &String::operator+=(const std::wstring &wstr) {
        return operator+=(String(wstr));
    }

    Number &String::operator[](uintmax index) {
        if (this->value != nullptr && index < this->value->size()) {
            return this->value->get(index);
        }
        throw createException2("String", "Wrong index");
    }

    bool String::operator==(String str) const {
        if (size() != str.size()) {
            return false;
        }

        for (int i = 0; i < size(); i++) {
            if (charAt(i) != str.charAt(i)) {
                return false;
            }
        }

        return true;
    }

    bool String::operator==(Number unicodeChar) const {
        return size() == 1 && charAt(0) == unicodeChar;
    }

    bool String::operator==(const char &ch) const {
        return operator==(Number(ch));
    }

    bool String::operator==(const wchar_t &wch) const {
        return operator==(Number(wch));
    }

    bool String::operator==(const char *str) const {
        return operator==(String(str));
    }

    bool String::operator==(const wchar_t *wstr) const {
        return operator==(String(wstr));
    }

    bool String::operator==(const std::string &str) const {
        return operator==(String(str));
    }

    bool String::operator==(const std::wstring &wstr) const {
        return operator==(String(wstr));
    }

    String String::toLower() {
        String result = String(this->size());

        for (int i = 0; i < this->size(); ++i) {
            result.value->set(std::tolower(this->charAt(i).getInt32()), i);
        }

        return std::move(result);
    }

    String String::toUpper() {
        String result = String(this->size());

        for (int i = 0; i < this->size(); ++i) {
            result.value->set(std::toupper(this->charAt(i).getInt32()), i);
        }

        return std::move(result);
    }

    int StringComparator::compare(const String &a, const String &b) const {
        NumberComparator comp;
        for (uintmax i = 0; i < a.size() && i < b.size(); i++) {
            int compResult = comp.compare(a.charAt(i), b.charAt(i));
            if (compResult != 0) {
                return compResult;
            }
        }
        return a.size() > b.size() ? 1 : (a.size() == b.size() ? 0 : -1);
    }
};