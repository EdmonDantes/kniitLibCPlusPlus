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
        Status(T value) {
            this->value = value;
        };

        Status(Status& value) {
            this->value = mask.value;
        }

        Status& operator=(Status& value) {
            this->value = mask.value;
            return *this;
        }

        bool check(uint8_t bitIndex) {
            return (value & (1 << bitIndex)) != 0;
        }

        void add(uint8_t bitIndex) {
            value = value | (1 << bitIndex);
        }

        void remove(uint8_t bitIndex) {
            value = value & (~(1 << bitIndex));
        }

        void clear() {
            this->value = 0;
        }

        bool isEmpty() {
            return this->value == 0;
        }
    };
};

#endif //KNIITLIBRARY_STATUS_H
