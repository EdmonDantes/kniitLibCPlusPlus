/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Custom implementation list template
 */

#ifndef KNIITLIBRARY_LIST_H
#define KNIITLIBRARY_LIST_H
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

        void move(T& a, T& b) {
            a = std::move(b);
        }
     protected:
        T* value = nullptr;
        uintmax _size = 0;
        uintmax capacity = 0;

        /**
         * Init/reinit array for contain values. If reinit delete all values.
         *
         * @param capacity - size of array.
         */
        void init(uintmax capacity) {
            this->_size = 0;
            this->capacity = capacity;

            if (value != nullptr) {
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
            if (value == nullptr) {
                value = new T[newSize];
                return;
            }

            T* tmp = new T[newSize];
            for (uintmax i = 0; i < _size && i < newSize; i++) {
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
            if (_size + additionalSize > capacity) {
                resize(capacity = (_size + max((_size * 2 / 3), additionalSize)));
            }
            _size += additionalSize;
            return true;
        }

     public:

        /**
         * Constructor with initialization array's length
         * @param capacity - initialization array's length
         */
        explicit List(const uintmax capacity) {
            init(capacity);
        };

        /**
         * Default constructor.
         * Default array's length = 16
         */
        List() : List(16) {
        };


        /**
         * Constructor from array
         */
        List(T* array, uintmax length, bool createNew = true) {
            if (!createNew) {
                value = array;
                _size = capacity = length;
            } else {
                init(length + (length * 3 / 2));
                memcpy(this->value, array, sizeof(*this->value) * length);
                this->_size = length;
            }
        }

        /**
         * Copy constructor
         */
        List(const List<T>& list) : List(list.size() + (list.size() * 3 / 2)) {
            memcpy(this->value, list.value, sizeof(*this->value) * list.size());
            this->_size = list._size;
        }

        /**
         * Move constructor
         */
        List(List<T>&& list) {
            operator=(std::move(list));
        }

        /**
         * Move operator
         */
        List<T>& operator=(List<T>&& list) {
            memcpy(this, &list, sizeof(*this));
            list.value = nullptr;
            list._size = 0;
            list.capacity = 0;
            return *this;
        }

        /**
         * Copy operator
         */
        List<T>& operator=(const List<T>& list) {
            this->init(max(list._size + (list._size * 3 / 2), 16));

            for (int i = 0; i < list._size; i++) {
                this->value[i] = list.value[i];
            }

            this->_size = list._size;

            return *this;
        }

        /**
         * Destructor.
         */
        ~List() {
            if (value != nullptr) {
                delete[] value;
            }

            this->value = nullptr;
            this->_size = 0;
            this->capacity = 0;
        }

        /**
         * Add new value to end of list
         *
         * @param value - new value
         */
        void add(const T& value) {
            if (addSize(1)) {
                move(this->value[_size - 1], const_cast<T&>(value));
            } else {
                throw createException2("ArrayList", "Can not add value");
            }
        }

        /**
         * Add new value to the list in special place with special index
         * @param value
         * @param index
         */
        void add(const T& value, int index) {
            if (index <= size()) {
                if (addSize(1)) {
                    for (uintmax i = size() - 1; i > index; i--) {
                        this->value[i] = this->value[i - 1];
                    }

                    move(this->value[index], const_cast<T&>(value));
                } else {
                    throw createException2("ArrayList", "Can not add value");
                }
            } else {
                throw createException2("ArrayList", "Wrong index");
            }
        }

        /**
         * Replace value in list in place with index
         * @param value
         * @param index
         */
        void set(const T& value, int index) {
            if (index < size()) {
                move(this->value[index], const_cast<T&>(value));
            } else if (index == size()) {
                this->add(value);
            } else {
                throw createException2("ArrayList", "Wrong index");
            }
        }

        /**
         * Add all values from list to current list.
         *
         * @param list - list with values
         */
        void addAll(const List<T>& list) {
            uintmax newSize = max(this->capacity, _size + list._size);
            resize(newSize);

            for (uintmax i = 0; i < list._size; i++) {
                add(list.value[i]);
            }
        }

        /**
         * Add all values from array to current list
         * @param array array with values
         * @param length count values in array
         */
        void addAll(const T* array, uintmax length) {
            uintmax newSize = max(this->capacity, _size + length);
            resize(newSize);

            for (uintmax i = 0; i < length; i++) {
                add(array[i]);
            }
        }

        /**
         * Remove value with index from current list
         *
         * @param index - index of value
         * @return Does remove value from this index. If list doesn't have this index, it will return false.
         */
        bool remove(uintmax index) {
            if (index < _size) {
                for (uintmax i = index; i < _size - 1; i++) {
                    value[index] = value[index + 1];
                }
                _size--;
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
            _size = 0;
            return true;
        }

        /**
         * Remove unused array's cells in memory
         *
         * @return Does remove unused array's cells in memory
         */
        bool cut() {
            if (_size < capacity) {
                resize(_size);
                return true;
            }
            return false;
        }

        /**
         * Change direction of list
         *
         * @return new list with changed direction
         */
        List<T> reverse() const {
            List<T> result = List<T>(_size);
            for (uintmax i = 0; i < _size; i++) {
                result.add(value[_size - i - 1]);
            }
            return std::move(result);
        }

        /**
         * Get value from index
         *
         * @param index - value's index
         * @return value
         */
        T& get(uintmax index) {
            if (index < _size) {
                return value[index];
            } else {
                throw createException2("List", "Wrong index");
            }
        }

        /**
         * @return count values in list
         */
        uintmax size() const {
            return _size;
        }

        /**
         * Find value in list
         * @tparam F equals function bool (T, T)
         * @param value value for find
         * @param func equals function
         * @return True if list contains value
         */
        template<typename F>
        bool find(const T& value, F func) const {
            for (int i = 0; i < _size; ++i) {
                if (func(this->value[i], value)) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Change size of this list
         * @param size New list's size
         * @param removeData If true, can remove some data
         * @return True, if list was changed size.
         */
        bool setSize(uintmax size, bool removeData = false) {
            if (size < _size) {
                if (removeData) {
                    _size = size;
                    return true;
                } else {
                    return false;
                };
            } else {
                return addSize(_size - size);
            }
        }

        /**
         * @return count all array's cells in list
         */
        uintmax getCapacity() const {
            return capacity;
        }

        /**
         * @return Array, if it possible, else return nullptr
         */
        T* toArray() const {
            if (this->value == nullptr) {
                return nullptr;
            }

            T* array = new T[size()];
            memcpy(array, this->value, size() * sizeof(T));
            return array;
        }

        /**
         * Add value to list
         *
         * @param value
         * @return this list
         */
        List<T>& operator<<(const T& value) {
            add(value);
            return *this;
        }

        /**
         * Get const value from index
         *
         * @param index - value's index
         * @return value
         */
        const T& operator[](uintmax index) const {
            if (index < _size) {
                return value[index];
            } else {
                throw createException2("List", "Wrong index");
            }
        }
    };

}

#endif //KNIITLIBRARY_LIST_H
