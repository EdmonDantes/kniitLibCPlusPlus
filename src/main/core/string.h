/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_STRING_H
#define KNIITLIBRARY_STRING_H
#include "core.h"
#include "codec.h"
#include "number.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS String {
    private:
        List<Number>* value = nullptr;

        String(uintmax countOfChar);

        void addChar(Number ch);

    public:

        String();
        String(const char& ch);
        String(const wchar_t& wch);
        String(const char* str);
        String(const wchar_t* wstr);
        String(const char* str, uintmax size);
        String(const wchar_t* str, uintmax size);
        String(const std::string& str);
        String(const std::wstring& wstr);
        String(List<uint8_t>& bytes, const Codec* codec, ByteOrder byteOrder = DEFAULT_BYTE_ORDER);

        String(const String& str);
        String(String&& str);

        ~String();

        uintmax size() const;

        bool isEmpty() const;

        const Number& charAt(uintmax index) const;
        String substring(uintmax startIndex) const;
        String substring(uintmax startIndex, uintmax endIndex) const;
        String reverse() const;

        std::string toString() const;
        std::wstring toWString() const;

        List<uint8_t> to(const Codec* codec, bool addZeroToEnd = false, ByteOrder byteOrder = DEFAULT_BYTE_ORDER) const;

        String& operator=(String str);
        String& operator=(Number unicodeChar);
        String& operator=(const char& ch);
        String& operator=(const wchar_t& wch);
        String& operator=(const char* str);
        String& operator=(const wchar_t* wstr);
        String& operator=(const std::string& str);
        String& operator=(const std::wstring& wstr);

        String operator+(String str) const;
        String operator+(Number unicodeChar) const;
        String operator+(const char& ch) const;
        String operator+(const wchar_t& wch) const;
        String operator+(const char* str) const;
        String operator+(const wchar_t* wstr) const;
        String operator+(const std::string& str) const;
        String operator+(const std::wstring& wstr) const;

        String& operator+=(String str);
        String& operator+=(Number unicodeChar);
        String& operator+=(const char& ch);
        String& operator+=(const wchar_t& wch);
        String& operator+=(const char* str);
        String& operator+=(const wchar_t* wstr);
        String& operator+=(const std::string& str);
        String& operator+=(const std::wstring& wstr);

        bool operator==(String str) const;
        bool operator==(Number unicodeChar) const;
        bool operator==(const char& ch) const;
        bool operator==(const wchar_t& wch) const;
        bool operator==(const char* str) const;
        bool operator==(const wchar_t* wstr) const;
        bool operator==(const std::string& str) const;
        bool operator==(const std::wstring& wstr) const;

        Number& operator[](uintmax index);

        String toLower();
        String toUpper();
    };

    KNIIT_LIB_CLASS StringComparator : public Comparator<String> {
        int compare(const String& a, const String& b) const override;
    };
};
#endif //KNIITLIBRARY_STRING_H
