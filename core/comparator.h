/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

#ifndef KNIITLIBRARY_COMPARATOR_H
#define KNIITLIBRARY_COMPARATOR_H
#include "core.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS Comparator {
    public:
            virtual int compare(const T& a, const T& b) const NO_BODY;
    };
}
#endif //KNIITLIBRARY_COMPARATOR_H
