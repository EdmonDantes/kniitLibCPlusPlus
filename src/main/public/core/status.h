/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_STATUS_H
#define KNIITLIBRARY_STATUS_H
#include "core.h"

KNIIT_LIB_NAMESPACE {
    template <typename T>
    KNIIT_LIB_CLASS Status {
    private:
        T value;
    public:
        Status() {
            this->value = 0;
        }

        explicit Status(T value) {
            this->value = value;
        };

        Status(Status& value) {
            this->value = value.value;
        }

        Status& operator=(const Status& value) = default;
        Status& operator=(const T& value) {
            this->value = value;
            return *this;
        }

        T getValue() const {
            return value;
        }

        bool check(uint8 bitIndex) const {
            return (value & (1 << bitIndex)) != 0;
        }

        bool checkMask(T value) const {
            return (this->value & value) == value;
        }

        void add(uint8 bitIndex) {
            value = value | (1 << bitIndex);
        }

        void remove(uint8 bitIndex) {
            value = value & (~(1 << bitIndex));
        }

        void clear() {
            this->value = 0;
        }

        bool isEmpty() const {
            return this->value == 0;
        }
    };
};

#endif //KNIITLIBRARY_STATUS_H
