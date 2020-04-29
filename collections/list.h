/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Custom implementation list template
 */

#ifndef KNIITLIBRARY_LIST_H
#define KNIITLIBRARY_LIST_H
#include <utility>
#include "../core/core.h"
#include "../core/exception.h"

KNIIT_LIB_NAMESPACE {

template <class T>
KNIIT_LIB_CLASS List {
private:

    /**
     * Return max value
     *
     * @param a
     * @param b
     * @return a > b ? a : b
     */
    uintmax max(uintmax a, uintmax b) {
        return a > b ? a : b;
    }

    void move(T& a, T& b){
        a = std::move(b);
    }
protected:
        T* value = 0;
        uintmax innerSize = -1;
        uintmax capacity = -1;

        /**
         * Init/reinit array for contain values. If reinit delete all values.
         *
         * @param capacity - size of array.
         */
        void init(uintmax capacity) {
            this->innerSize = 0;
            this->capacity = capacity;

            if (value != nullptr && value != 0) {
                delete[] value;
            }

            value = new T[capacity];
        }

        /**
         * Change size of inner array.
         * If newSize less than current array length, part of values will be lost.
         * If newSize more than current array length, new array's cells may contain random values.
         *
         * @param newSize - new size of array.
         */
        void resize(uintmax newSize) {
            if (value == nullptr || value == 0) {
                value = new T[newSize];
                return;
            }

            T* tmp = new T[newSize];
            for (uintmax i = 0; i < innerSize && i < newSize; i++) {
                move(tmp[i], value[i]);
            }
            delete[] value;
            value = tmp;
        }

        /**
         * Add size to current array size. Save all current data.
         * In new array's cells may contain random values.
         *
         * @param additionalSize - how much add to current array size
         * @return Does increase array size on additionalSize.
         */
        bool addSize(uintmax additionalSize) {
            if (innerSize + additionalSize >= capacity) {
                resize(capacity = (innerSize + max((innerSize * 2 / 3), additionalSize)));
            }
            innerSize += additionalSize;
            return true;
        }
        public:

        /**
         * Constructor with initialization array's length
         * @param capacity - initialization array's length
         */
        explicit List(uintmax capacity) {
            init(capacity);
        };

        /**
         * Default constructor.
         * Default array's length = 16
         */
        List() : List(16) {};

        /**
         * Copy constructor
         */
        List(const List<T>& list) : List(list.size() + (list.size() * 3 / 2)) {
            memcpy(this->value, list.value, sizeof(*this->value) * list.size());
            this->innerSize = list.innerSize;
        }

        /**
         * Move constructor
         */
        List(List<T>&& list) {
            memcpy(this, &list, sizeof(*this));
            list.value = 0;
            list.innerSize = 0;
            list.capacity = 0;
        }

        /**
         * Move operator
         */
        List<T>& operator = (List<T>&& list) {
            memcpy(this, &list, sizeof(*this));
            list.value = 0;
            list.innerSize = 0;
            list.capacity = 0;
            return *this;
        }

        /**
         * Copy operator
         */
        List<T>& operator = (const List<T>& list) {
            this->init(list.innerSize + (list.innerSize * 3 / 2));

            for (int i = 0; i < list.innerSize; i++) {
                this->value[i] = list.value[i];
            }

            this->innerSize = list.innerSize;

            return *this;
        }

        /**
         * Destructor.
         */
        ~List() {
            if (value != nullptr && value != 0) {
                delete[] value;
            }

            this->value = 0;
            this->innerSize = 0;
            this->capacity = 0;
        }

        /**
         * Add new value to end of list
         *
         * @param value - new value
         */
        void add(const T& value) {
            if (addSize(1)) {
                move(this->value[innerSize - 1], const_cast<T&>(value));
            } else {
                throw createException2("ArrayList", "Can not add value");
            }
        }

        /**
         * Add all values for list to current list.
         *
         * @param list - list with values
         */
        void addAll(List<T>& list) {
            uintmax newSize = max(this->capacity, innerSize + list.innerSize);
            resize(newSize);

            for (uintmax i = 0; i < list.innerSize; i++) {
                add(list.value[i]);
            }
        }

        /**
         * Remove value with index from current list
         *
         * @param index - index of value
         * @return Does remove value from this index. If list doesn't have this index, it will return false.
         */
        bool remove(uintmax index) {
            if (index < innerSize) {
                for (uintmax i = index; i < innerSize - 1; i++) {
                    value[index] = value[index + 1];
                }
                innerSize--;
                return true;
            }
            return false;
        }

        /**
         * Remove all values from current list
         * This values may stay in memory, and it may not call deconstuctor for this objects.
         * Not less array's length in memory
         *
         * @return Does remove all values
         */
        bool clear() {
            innerSize = 0;
            return true;
        }

        /**
         * Remove unused array's cells in memory
         *
         * @return Does remove unused array's cells in memory
         */
        bool cut() {
            if (innerSize < capacity) {
                resize(innerSize);
                return true;
            }
            return false;
        }

        /**
         * Change direction of list
         *
         * @return new list with changed direction
         */
        List<T>& reverse() const {
            List<T> result(innerSize);
            for (uintmax i = 0; i < innerSize; i++) {
                result.value[i] = value[innerSize - i - 1];
            }
            return result;
        }

        /**
         * Get value from index
         *
         * @param index - value's index
         * @return value
         */
        T& get(uintmax index) {
            if (index < innerSize) {
                return value[index];
            }
            throw "Wrong index";
        }

        /**
         * @return count values in list
         */
        uintmax size() const {
            return innerSize;
        }

        /**
         * @return count all array's cells in list
         */
        uintmax getCapacity() const {
            return capacity;
        }

        /**
         * Add value to list
         *
         * @param value
         * @return this list
         */
        List<T>& operator<< (const T& value) {
            add(value);
            return *this;
        }

        /**
         * Get const value from index
         *
         * @param index - value's index
         * @return value
         */
        const T& operator[] (uintmax index) const {
            if (index < innerSize) {
                return value[index];
            }
            throw "Wrong index";
        }
};


}

#endif //KNIITLIBRARY_LIST_H
