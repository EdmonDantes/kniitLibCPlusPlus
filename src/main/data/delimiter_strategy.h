/*
 *      Copyright (c). 2021. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */


#ifndef KNIITLIBRARY_SRC_MAIN_DATA_DELIMITER_STRATEGY_H_
#define KNIITLIBRARY_SRC_MAIN_DATA_DELIMITER_STRATEGY_H_
#include "../core/core.h"
#include "../core/number.h"
#include "../collections/list.h"

KNIIT_LIB_NAMESPACE {
    KNIIT_LIB_CLASS DelimiterStrategy {
     private:
        List<Number> delimiters;
        bool skipDelimiters = true;
        bool removeDelimiters = false;
     public:
        /**
         * Create DelimiterStrategy object
         * @param delimiters All delimiters
         * @param skipDelimiters If true stream position will be on char after delimiter
         * @param removeDelimiters If true in destroyer will call List destroyer
         */
        DelimiterStrategy(List<Number>&& delimiters, bool skipDelimiters, bool removeDelimiters = true) {
            this->delimiters = std::move(delimiters);
            this->skipDelimiters = skipDelimiters;
            this->removeDelimiters = removeDelimiters;
        }

        DelimiterStrategy(List<Number>& delimiters, bool skipDelimiters, bool removeDelimiters = true) {
            this->delimiters = delimiters;
            this->skipDelimiters = skipDelimiters;
            this->removeDelimiters = removeDelimiters;
        }

        DelimiterStrategy(Number delimiter, bool skipDelimiter) : DelimiterStrategy(List<Number>(new Number[1] {delimiter }, 1, false), skipDelimiter, true) {}
        DelimiterStrategy(Number delimiter0, Number delimiter1, bool skipDelimiters) : DelimiterStrategy(List<Number>(new Number[2]{ delimiter0, delimiter1}, 2, false), skipDelimiters, true){}
        DelimiterStrategy(Number* delimiters, uintmax size, bool skipDelimiters) : DelimiterStrategy(List<Number>(delimiters, size, false), skipDelimiters, false) {}

        DelimiterStrategy(DelimiterStrategy& delimiterStrategy) {
            this->delimiters = delimiterStrategy.delimiters;
            this->skipDelimiters = delimiterStrategy.skipDelimiters;
            this->removeDelimiters = true;
        }

        DelimiterStrategy(DelimiterStrategy&& delimiterStrategy) {
            this->delimiters = std::move(delimiterStrategy.delimiters);
            this->skipDelimiters = delimiterStrategy.skipDelimiters;
            this->removeDelimiters = delimiterStrategy.removeDelimiters;
            delimiterStrategy.removeDelimiters = true;
        }

        void add(const Number& ch) {
            delimiters.add(ch);
        }

        DelimiterStrategy plus(const Number& ch, bool skipDelimiters) const {
            List<Number> tmp = List<Number>(delimiters.size() + 1);
            tmp.addAll(delimiters);
            tmp.add(ch);
            return std::move(DelimiterStrategy(std::move(tmp), skipDelimiters, true));
        }

        List<Number>* getDelimiters() {
            return &delimiters;
        }

        bool hasDelimiter(Number ch) const {
            return delimiters.find(ch, [](Number a, Number b) { return a == b; });
        }

        bool isSkipDelimiters() const {
            return skipDelimiters;
        }

        ~DelimiterStrategy() {
            if (removeDelimiters) {
                delimiters.~List();
            }
        }
    };
};
#endif //KNIITLIBRARY_SRC_MAIN_DATA_DELIMITER_STRATEGY_H_
