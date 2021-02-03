/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Main class for common describe all number's types
 * You can create object of this class from any number any types
 * You can get number with any types
 *
 * Fixed status doesn't allow change type of number. Default, number change inner type, if it need.
 */

#ifndef KNIITLIBRARY_NUMBER_H
#define KNIITLIBRARY_NUMBER_H

#include "core.h"
#include "comparator.h"
#include "status.h"

KNIIT_LIB_NAMESPACE {

    KNIIT_LIB_CLASS Number {
    private:

        /*
            Status bits:
            0 - Fixed status
            1 - 8 bit
            2 - 16 bit
            3 - 32 bit
            4 - 64 bit (in x32 - haven`t value)
            5 - Signed value
            6 - float value
            7 - double value

            Fixed status mean you can not change number type
            Signed bit all be 1 if used decimal value
        */
        uint8_t status;
        uint8_t* number[8];

        static const uint8_t IS_FIXED_STATUS = 1;

        static const uint8_t IS_USE_8_BIT = 2;
        static const uint8_t IS_USE_16_BIT = 4;
        static const uint8_t IS_USE_32_BIT = 8;
        static const uint8_t IS_USE_64_BIT = 16;

        static const uint8_t IS_SIGNED_VALUE = 32;

        static const uint8_t IS_UINT8 = IS_USE_8_BIT;
        static const uint8_t IS_UINT16 = IS_USE_16_BIT;
        static const uint8_t IS_UINT32 = IS_USE_32_BIT;
        #ifdef KNIIT_LIB_USE_X64
        static const uint8_t IS_UINT64 = IS_USE_64_BIT;
        #endif

        static const uint8_t IS_INT8 = IS_USE_8_BIT | IS_SIGNED_VALUE;
        static const uint8_t IS_INT16 = IS_USE_16_BIT | IS_SIGNED_VALUE;
        static const uint8_t IS_INT32 = IS_USE_32_BIT | IS_SIGNED_VALUE;
        #ifdef KNIIT_LIB_USE_X64
        static const uint8_t IS_INT64 = IS_USE_64_BIT | IS_SIGNED_VALUE;
        #endif

        static const uint8_t IS_FLOAT = IS_USE_32_BIT | IS_SIGNED_VALUE | 64;
        static const uint8_t IS_DOUBLE = IS_USE_64_BIT | IS_SIGNED_VALUE | 128;

        static const uint8_t IS_REAL = IS_FLOAT | IS_DOUBLE;

        static const uint8_t IS_UINT =
                IS_UINT8
                | IS_UINT16
                | IS_UINT32
        #ifdef KNIIT_LIB_USE_X64
        | IS_UINT64
        #endif
        ;
        static const uint8_t IS_INT =
                IS_INT8
                | IS_INT16
                | IS_INT32
        #ifdef KNIIT_LIB_USE_X64
        | IS_INT64
        #endif
        ;


        bool checkStatus() const;
        bool checkNumber() const;
        bool checkMask(uint8_t mask) const;

        bool isFixed() const;

        inline uint8_t* getPointer(int lowBytes = 0) const;

        template <typename T>
        T get() const;

        bool setStatus(bool isInteger, bool isSigned, int innerSize);

        template <typename T>
        bool set(T number, bool isInteger, bool isSigned, int innerSize);

        void init(uint8_t status, uint8_t* number);

        template <typename T>
        Number(uint8_t status, T number);

        template <typename F>
        void selfArifmeticFunction(const Number& value, F func);
    public:


        Number();
        Number(int8_t number, bool isFixed = false);
        Number(int16_t number, bool isFixed = false);
        Number(int32_t number, bool isFixed = false);
        Number(uint8_t number, bool isFixed = false);
        Number(uint16_t number, bool isFixed = false);
        Number(uint32_t number, bool isFixed = false);
        Number(float number, bool isFixed = false);
        Number(double number, bool isFixed = false);
        Number(uint8_t* number, uintmax innerSize, bool isFixed = false);
        Number(const Number& number);

        ~Number();

        bool isSigned() const;
        bool isReal() const;
        bool isInteger() const;
        bool isNAN() const;

        bool isInt() const;
        bool isUInt() const;
        bool isInt8() const;
        bool isInt16() const;
        bool isInt32() const;
        bool isUInt8() const;
        bool isUInt16() const;
        bool isUInt32() const;
        bool isFloat() const;
        bool isDouble() const;

        int size() const;

        intmax getInt() const;
        uintmax getUInt() const;

        int8_t getInt8() const;
        int16_t getInt16() const;
        int32_t getInt32() const;
        uint8_t getUInt8() const;
        uint16_t getUInt16() const;
        uint32_t getUInt32() const;

        float getFloat() const;
        double getDouble() const;

        uint8_t* getBytes();

        Number operator+(const Number& value);
        Number operator-(const Number& value);
        Number operator*(const Number& value);
        Number operator/(const Number& value);
        Number& operator=(const Number& value);

        Number& operator+=(const Number& value);
        Number& operator-=(const Number& value);
        Number& operator*=(const Number& value);
        Number& operator/=(const Number& value);

        bool operator>(const Number& value) const;
        bool operator<(const Number& value) const;
        bool operator>=(const Number& value) const;
        bool operator<=(const Number& value) const;
        bool operator==(const Number& value) const;
        bool operator!=(const Number& value) const;

        Number operator&(const Number& value);
        Number operator|(const Number& value);
        Number operator<<(const Number& value);
        Number operator>>(const Number& value);

        Number operator-();

        #ifdef KNIIT_LIB_USE_X64
        Number(int64_t number, bool isFixed = false);
        Number(uint64_t number, bool isFixed = false);

        bool isInt64() const;
        bool isUInt64() const;
        int64_t getInt64() const;
        uint64_t getUInt64() const;
        #endif // KNIIT_LIB_USE_X64
    };

    KNIIT_LIB_CLASS NumberComparator : public Comparator<Number> {
    public:
        int compare(const Number& a, const Number& b) const override;
    };
}
#endif //KNIITLIBRARY_NUMBER_H
