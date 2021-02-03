/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Custom iterator interface
 */

#ifndef KNIITLIBRARY_ITERATOR_H
#define KNIITLIBRARY_ITERATOR_H
#include "../core/core.h"

KNIIT_LIB_NAMESPACE {

    template <class T>
    KNIIT_LIB_CLASS Iterator {
    public:
        /**
         * Must be implement.
         * @return Does iterator have next element.
         */
        virtual bool hasNext() NO_BODY;

        /**
         * Must be implement.
         * @return Next element in iterator.
         */
        virtual T& next() NO_BODY;

        /**
         * May be return exception.
         * @return Does iterator remove element which was last return from next() method.
         */
        virtual bool remove() NO_BODY;

        /**
         * Virtual destructor.
         */
        virtual ~Iterator(){};
    };
}
#endif //KNIITLIBRARY_ITERATOR_H
