/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#include "core/number.h"
#include "core/exception.h"

KNIIT_LIB_NAMESPACE {

    bool Number::checkStatus() const {
        return status != 0 && status != 1;
    }

    bool Number::checkNumber() const {
        return checkStatus();
    }

    bool Number::checkMask(uint8 mask) const {
        return (status & mask) == mask;
    }

    bool Number::isFixed() const {
        return checkMask(IS_FIXED_STATUS);
    }

    inline uint8* Number::getPointer(int lowBytes) const {
        return ((uint8*)&number) + (lowBytes > 0 ? (sizeof(number) - lowBytes) : 0);
    }

    bool Number::setStatus(bool isInteger, bool isSigned, int size) {

        if (this->isInteger() == isInteger && this->isSigned() == isSigned && this->size() == size) {
            return true;
        }

        switch (size) {
            case 1:
                if (isInteger) {
                    this->status = isSigned ? IS_INT8 : IS_UINT8;
                } else {
                    this->status = IS_USE_8_BIT;
                }
                break;
            case 2:
                if (isInteger) {
                    this->status = isSigned ? IS_INT16 : IS_UINT16;
                } else {
                    this->status = IS_USE_16_BIT;
                }
                break;
            case 4:
                if (isInteger) {
                    this->status = isSigned ? IS_INT32 : IS_UINT32;
                } else if (isSigned) {
                    this->status = IS_FLOAT;
                } else {
                    this->status = IS_USE_32_BIT;
                }
                break;
            case 8:
                #ifdef KNIIT_LIB_USE_X64
                if (isInteger) {
                    this->status = isSigned ? IS_INT64 : IS_UINT64;
                } else
                    #endif
                if (isSigned) {
                    this->status = IS_DOUBLE;
                } else {
                    this->status = IS_USE_64_BIT;
                }
                break;
            default:return false;
        }

        return true;
    }

    template <typename T>
    T Number::get() const {
        if (!checkNumber()) {
            throw createException2("Number", "Can not get value from number, because it is NAN");
        }

        if (isInt8()) {
            return (T)*((int8*)getPointer(1));
        } else if (isInt16()) {
            return (T)*((int16*)getPointer(2));
        } else if (isInt32()) {
            return (T)*((int32*)getPointer(4));
        } else if (isUInt8()) {
            return (T)*((uint8*)getPointer(1));
        } else if (isUInt16()) {
            return (T)*((uint16*)getPointer(2));
        } else if (isUInt32()) {
            return (T)*((uint32*)getPointer(4));
        } else if (isFloat()) {
            return (T)*((float*)getPointer(sizeof(float)));
        } else if (isDouble()) {
            return (T)*((double*)getPointer(sizeof(double)));
        }
            #ifdef KNIIT_LIB_USE_X64
        else if (isInt64()) {
            return (T)*((int64*)getPointer());
        } else if (isUInt64()) {
            return (T)*((uint64*)getPointer());
        }
            #endif // KNIIT_LIB_USE_X64
        else {
            throw createException2("Number", "Illegal status of number");
        }
        return 0;
    }

    template <typename T>
    bool Number::set(T number, bool isInteger, bool isSigned, int size) {
        if (isFixed()) {
            if (size > this->size()) {
                return false;
            }

            if (isUInt() && (!isInteger || isSigned) || isInt() && !isInteger) {
                return false;
            }
        }

        *((T*)getPointer(size)) = number;
        return setStatus(isInteger, isSigned, size);
    }

    void Number::init(uint8 status, uint8* number) {
        this->status = status;
        set(number, isInteger(), isSigned(), 0);
    }

    template <typename T>
    Number::Number(uint8 status, T number) {
        this->status = status;
        set(number, isInteger(), isSigned(), size());
    }

    Number::Number() : Number((uint8)0, 0) {
    }

    Number::Number(int8 number, bool isFixed) : Number((uint8)(isFixed ? IS_INT8 | IS_FIXED_STATUS : IS_INT8), number) {
    }

    Number::Number(int16 number, bool isFixed) : Number((uint8)(isFixed ? IS_INT16 | IS_FIXED_STATUS : IS_INT16),
        number) {
    }

    Number::Number(int32 number, bool isFixed) : Number((uint8)(isFixed ? IS_INT32 | IS_FIXED_STATUS : IS_INT32),
        number) {
    }

    Number::Number(uint8 number, bool isFixed) : Number((uint8)(isFixed ? IS_UINT8 | IS_FIXED_STATUS : IS_UINT8),
        number) {
    }

    Number::Number(uint16 number, bool isFixed) : Number((uint8)(isFixed ? IS_UINT16 | IS_FIXED_STATUS : IS_UINT16),
        number) {
    }

    Number::Number(uint32 number, bool isFixed) : Number((uint8)(isFixed ? IS_UINT32 | IS_FIXED_STATUS : IS_UINT32),
        number) {
    }

    Number::Number(float number, bool isFixed) : Number((uint8)(isFixed ? IS_FLOAT | IS_FIXED_STATUS : IS_FLOAT),
        number) {
    }

    Number::Number(double number, bool isFixed) : Number((uint8)(isFixed ? IS_DOUBLE | IS_FIXED_STATUS : IS_DOUBLE),
        number) {
    }

    Number::Number(uint8* number, uintmax size, bool isFixed) {
        memcpy(getPointer(size > 7 ? 0 : size), number, size > 7 ? 0 : size);
        setStatus(false, false, size);
        status |= isFixed ? IS_FIXED_STATUS : 0;
    }

    Number::Number(const Number& number) {
        this->status = number.status;
        memcpy(this->number, number.number, 8);
    }

    Number::~Number() {
        this->status = 0;
    }

    bool Number::isSigned() const {
        return checkMask(IS_SIGNED_VALUE);
    }

    int Number::size() const {

        if (!checkStatus()) {
            return 0;
        }

        if (checkMask(IS_USE_8_BIT)) {
            return 1;
        } else if (checkMask(IS_USE_16_BIT)) {
            return 2;
        } else if (checkMask(IS_USE_32_BIT)) {
            return 4;
        } else if (checkMask(IS_USE_64_BIT)) {
            return 8;
        } else {
            return 0;
        }
    }

    bool Number::isReal() const {
        return isFloat() || isDouble();
    }

    bool Number::isInteger() const {
        return !isReal();
    }

    bool Number::isNAN() const {
        return !checkStatus();
    }

    bool Number::isInt() const {
        return isInteger() && isSigned();
    }

    bool Number::isUInt() const {
        return isInteger() && !isSigned();
    }

    bool Number::isInt8() const {
        return isInt() && checkMask(IS_USE_8_BIT);
    }

    bool Number::isInt16() const {
        return isInt() && checkMask(IS_USE_16_BIT);
    }

    bool Number::isInt32() const {
        return isInt() && checkMask(IS_USE_32_BIT);
    }

    bool Number::isUInt8() const {
        return isUInt() && checkMask(IS_USE_8_BIT);
    }

    bool Number::isUInt16() const {
        return isUInt() && checkMask(IS_USE_16_BIT);
    }

    bool Number::isUInt32() const {
        return isUInt() && checkMask(IS_USE_32_BIT);
    }

    bool Number::isFloat() const {
        return checkMask(IS_FLOAT);
    }

    bool Number::isDouble() const {
        return checkMask(IS_DOUBLE);
    }

    intmax Number::getInt() const {
        return get<intmax>();
    }

    uintmax Number::getUInt() const {
        return get<uintmax>();
    }

    int8 Number::getInt8() const {
        return get<int8>();
    }

    int16 Number::getInt16() const {
        return get<int16>();
    }

    int32 Number::getInt32() const {
        return get<int32>();
    }

    uint8 Number::getUInt8() const {
        return get<uint8>();
    }

    uint16 Number::getUInt16() const {
        return get<uint16>();
    }

    uint32 Number::getUInt32() const {
        return get<uint32>();
    }

    float Number::getFloat() const {
        return get<float>();
    }

    double Number::getDouble() const {
        return get<double>();
    }

    uint8* Number::getBytes() {
        int count = size();
        uint8* result = new uint8[count];
        memcpy(result, getPointer(count), count);
        return result;
    }

    template <typename F>
    Number arifmeticFunction(const Number* a, const Number* b, F func) {
        if (a->isUInt() && b->isUInt()) {
            return func(a->getUInt(), b->getUInt());
        } else if ((a->isInt() || a->getUInt()) && (b->isInt() || b->isUInt())) {
            if (a->getInt() > 0 && b->getInt() > 0) {
                return func(a->getUInt(), b->getUInt());
            } else {
                return func(a->getInt(), b->getInt());
            }
        } else if (a->isFloat() && b->isFloat()) {
            return func(a->getFloat(), b->getFloat());
        } else {
            return func(a->getDouble(), b->getDouble());
        }
    }

    Number Number::operator+(const Number& value) {
        return arifmeticFunction(this, &value, [](auto a, auto b) { return a + b; });
    }

    Number Number::operator-(const Number& value) {
        return arifmeticFunction(this, &value, [](auto a, auto b) { return a - b; });
    }

    Number Number::operator*(const Number& value) {
        return arifmeticFunction(this, &value, [](auto a, auto b) { return a * b; });
    }

    Number Number::operator/(const Number& value) {
        return arifmeticFunction(this, &value, [](auto a, auto b) { return a / b; });
    }

    Number& Number::operator=(const Number& value) {
        memcpy(number, value.number, 8);
        status = value.status;
        return *this;
    }

    template <typename F>
    void Number::selfArifmeticFunction(const Number& value, F func) {
        const Number* futureType = value.status > status ? &value : this;
        int futureSize = size() > value.size() ? size() : value.size();

        if (futureType->isUInt()) {
            if (!set(func(this->getUInt(), value.getUInt()), true, false, futureSize)) {
                throw "Error";
            }
        } else if (futureType->isInt()) {
            if (value.getInt() >= 0 && this->getInt() >= 0) {
                if (!set(func(this->getUInt(), value.getUInt()), true, false, futureSize)) {
                    throw "Error";
                }
            } else {
                if (!set(func(this->getInt(), value.getInt()), true, true, futureSize)) {
                    throw "Error";
                }
            }
        } else if (futureType->isFloat()) {
            if (!set(func(this->getFloat(), value.getFloat()), false, true, futureSize)) {
                throw "Error";
            }
        } else if (futureType->isDouble()) {
            if (!set(func(this->getDouble(), value.getDouble()), false, true, futureSize)) {
                throw "Error";
            }
        }
    }

    Number& Number::operator+=(const Number& value) {
        selfArifmeticFunction(value, [](auto a, auto b) { return a + b; });
        return *this;
    }

    Number& Number::operator-=(const Number& value) {
        selfArifmeticFunction(value, [](auto a, auto b) { return a - b; });
        return *this;
    }

    Number& Number::operator*=(const Number& value) {
        selfArifmeticFunction(value, [](auto a, auto b) { return a * b; });
        return *this;
    }

    Number& Number::operator/=(const Number& value) {
        selfArifmeticFunction(value, [](auto a, auto b) { return a / b; });
        return *this;
    }

    bool Number::operator>(const Number& value) const {
        if (isDouble() || value.isDouble()) {
            return getDouble() > value.getDouble();
        } else if (isFloat() || value.isFloat()) {
            return getFloat() > value.getFloat();
        } else if (isInt() && value.isInt()) {
            return getInt() > value.getInt();
        } else {
            return getUInt() > value.getUInt();
        }
    }

    bool Number::operator<(const Number& value) const {
        if (isDouble() || value.isDouble()) {
            return getDouble() < value.getDouble();
        } else if (isFloat() || value.isFloat()) {
            return getFloat() < value.getFloat();
        } else if (isInt() && value.isInt()) {
            return getInt() < value.getInt();
        } else {
            return getUInt() < value.getUInt();
        }
    }

    bool Number::operator>=(const Number& value) const {
        return !operator<(value);
    }

    bool Number::operator<=(const Number& value) const {
        return !operator>(value);
    }

    bool Number::operator==(const Number& value) const {
        if (isDouble() || value.isDouble()) {
            return getDouble() == value.getDouble();
        } else if (isFloat() || value.isFloat()) {
            return getFloat() == value.getFloat();
        } else if (isInt() && value.isInt()) {
            return getInt() == value.getInt();
        } else {
            return getUInt() == value.getUInt();
        }
    }

    bool Number::operator!=(const Number& value) const {
        return !operator==(value);
    }

    Number Number::operator&(const Number& value) {
        if (value.isInteger()) {
            if (isInt() || value.isInt()) {
                return (getInt() & value.getInt());
            } else {
                return (getUInt() & value.getUInt());
            }
        } else {
            return *this;
        }
    }

    Number Number::operator|(const Number& value) {
        if (value.isInteger()) {
            if (isInt() || value.isInt()) {
                return (getInt() | value.getInt());
            } else {
                return (getUInt() | value.getUInt());
            }
        } else {
            return *this;
        }
    }

    Number Number::operator<<(const Number& value) {
        if (value.isInteger()) {
            if (isInt() || value.isInt()) {
                return (getInt() << value.getInt());
            } else {
                return (getUInt() << value.getUInt());
            }
        } else {
            return *this;
        }
    }

    Number Number::operator>>(const Number& value) {
        if (value.isInteger()) {
            if (isInt() || value.isInt()) {
                return (getInt() >> value.getInt());
            } else {
                return (getUInt() >> value.getUInt());
            }
        } else {
            return *this;
        }
    }

    Number Number::operator-() {
        if (isDouble()) {
            return -getDouble();
        } else if (isFloat()) {
            return -getFloat();
        } else if (isInteger()) {
            if (isUInt() && isFixed()) {
                throw "Status is fixed for unsigned integer value";
            } else {
                return -getInt();
            }
        } else {
            return Number((uint8)0, 0);
        }
    }

    #ifdef KNIIT_LIB_USE_X64

    Number::Number(int64 number, bool isFixed) : Number((uint8)(isFixed ? IS_INT64 | IS_FIXED_STATUS : IS_INT64),
        number) {
    }

    Number::Number(uint64 number, bool isFixed) : Number((uint8)(isFixed ? IS_UINT64 | IS_FIXED_STATUS : IS_UINT64),
        number) {
    }

    bool Number::isInt64() const {
        return isInt() && checkMask(IS_USE_64_BIT);
    }

    bool Number::isUInt64() const {
        return isUInt() && checkMask(IS_USE_64_BIT);
    }

    int64 Number::getInt64() const {
        return get<int64>();
    }

    uint64 Number::getUInt64() const {
        return get<uint64>();
    }

    #endif


    int NumberComparator::compare(const Number& a, const Number& b) const {
        if (a < b) {
            return -1;
        } else if (a == b) {
            return 0;
        } else {
            return 1;
        }
    }
}