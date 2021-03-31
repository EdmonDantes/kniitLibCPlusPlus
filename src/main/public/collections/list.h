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
        constexpr inline static uintmax max(uintmax a, uintmax b) noexcept {
            return a > b ? a : b;
        }

        constexpr inline static uintmax min(uintmax a, uintmax b) noexcept {
            return a < b ? a : b;
        }

        inline static void move(T& a, T& b) {
            a = std::move(b);
        }
     protected:

        struct ValueWithSize {
            uintmax size = 0;
            T* value = nullptr;
        };

     public:
        static constexpr uint8 maxNotAllocated = sizeof(ValueWithSize) / sizeof(T);

     protected:

        uintmax capacity = 0;

        union Store {
            ValueWithSize valueWithSize;

            struct ValueWithoutSize {
                T value[max(maxNotAllocated, 1)];
            } valueWithoutSize;

            Store() {}
            ~Store() {}
        } store;

        inline T* getPointer() const noexcept {
            return capacity > maxNotAllocated ? store.valueWithSize.value : const_cast<T*>(store.valueWithoutSize.value);
        }

        inline uintmax getSize() const noexcept {
            return capacity > maxNotAllocated ? store.valueWithSize.size : capacity;
        }

        inline bool isInStack() const noexcept {
            return capacity <= maxNotAllocated;
        }

        inline bool isInHeap() const noexcept {
            return capacity > maxNotAllocated;
        }

        void initInHeap(uintmax capacity) {
            this->capacity = capacity;
            store.valueWithSize.size = 0;
            store.valueWithSize.value = new T[capacity];
        }

        void initInStack() {
            capacity = 0;
        }

        void resizeInStack(uintmax newLength) {
            if (newLength != getCapacity() && newLength > maxNotAllocated) {
                T* tmp = new T[newLength];
                memcpy(tmp, store.valueWithoutSize.value, capacity * sizeof(T));

                uintmax size = capacity;
                capacity = newLength;

                store.valueWithSize.size = size;
                store.valueWithSize.value = tmp;
            }
        }

        void resizeInHeap(uintmax newLength) {
            if (newLength == getCapacity()) {
                return;
            }

            if (newLength <= maxNotAllocated) {
                T* tmp = store.valueWithSize.value;
                memcpy(store.valueWithoutSize.value, tmp, newLength * sizeof(T));

                delete[] tmp;
            } else {
                T* tmp = new T[newLength];
                memcpy(tmp, store.valueWithSize.value, min(store.valueWithSize.size, newLength) * sizeof(T));

                delete[] store.valueWithSize.value;
                store.valueWithSize.value = tmp;
                capacity = newLength;
            }
        }

        /**
         * Init/reinit array for contain values. If reinit delete all values.
         *
         * @param capacity - size of array.
         */
        void init(uintmax capacity) {
            if (capacity > maxNotAllocated) {
                initInHeap(capacity);
            } else {
                initInStack();
            }
        }

        /**
         * Change size of inner array.
         * If newSize less than current array length, part of values will be lost.
         * If newSize more than current array length, new array's cells may contain random values.
         *
         * @param newSize - new size of array.
         */
        void resize(uintmax newSize) {
            if (isInStack()) {
                resizeInStack(newSize);
            } else {
                resizeInHeap(newSize);
            }
        }

        /**
         * Add size to current array size. Save all current data.
         * In new array's cells may contain random values.
         *
         * @param additionalSize - how much add to current array size
         * @return Does increase array size on additionalSize.
         */
        bool addSize(uintmax additionalSize) {
            if (capacity > maxNotAllocated) {
                if (store.valueWithSize.size + additionalSize > capacity) {
                    resize(store.valueWithSize.size + max(store.valueWithSize.size * 2 / 3, additionalSize));
                }

                store.valueWithSize.size += additionalSize;
            } else {
                this->capacity += additionalSize;
            }

            return true;
        }

        bool removeSize(uintmax subSize) {
            if (isInStack()) {
                store.valueWithSize.size = store.valueWithSize.size < subSize ? 0 : store.valueWithSize.size - subSize;
            } else {
                capacity = capacity < subSize ? 0 : capacity - subSize;
            }
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
        List() : List(16) {};


        /**
         * Constructor from array
         */
        List(T* array, uintmax length, bool createNew = true) {
            if (length > maxNotAllocated) {
                if (!createNew) {
                    store.valueWithSize.value = array;
                    store.valueWithSize.size = capacity = length;
                } else {
                    init(length + (length * 3 / 2));
                    memcpy(store.valueWithSize.value, array, length * sizeof(T));
                    store.valueWithSize.size = length;
                }
            } else {
                memcpy(store.valueWithoutSize.value, array, length * sizeof(T));
                capacity = length;
            }
        }

        /**
         * Copy constructor
         */
        List(const List<T>& list) : List(list.size() + (list.size() * 3 / 2)) {
            memcpy(this->value, list.getPointer(), sizeof(*this->value) * list.size());
            setSize(list.getSize(), true);
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
            if (list.isInHeap()) {
                list.store.valueWithSize.value = nullptr;
                list.store.valueWithSize.size = 0;
            }

            list.capacity = 0;
            return *this;
        }

        /**
         * Copy operator
         */
        List<T>& operator=(const List<T>& list) {
            this->init(max(list.getSize() + (list.getSize() * 3 / 2), 16));

            for (int i = 0; i < list.getSize(); i++) {
                getPointer()[i] = list.getPointer()[i];
            }

            setSize(list.getSize(), true);

            return *this;
        }

        /**
         * Destructor.
         */
        ~List() {
            if (capacity > maxNotAllocated) {
                delete[] store.valueWithSize.value;
                store.valueWithSize.value = nullptr;
                store.valueWithSize.size = 0;
            }

            capacity = 0;
        }

        /**
         * Add new value to end of list
         *
         * @param value - new value
         */
        void add(const T& value) {
            if (addSize(1)) {
                move(getPointer()[getSize() - 1], const_cast<T&>(value));
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
                        getPointer()[i] = getPointer()[i - 1];
                    }

                    move(getPointer()[index], const_cast<T&>(value));
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
                move(getPointer()[index], const_cast<T&>(value));
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
            uintmax newSize = max(capacity, getSize() + list.getSize());
            resize(newSize);

            for (uintmax i = 0; i < list.getSize(); i++) {
                add(list.getPointer()[i]);
            }
        }

        /**
         * Add all values from array to current list
         * @param array array with values
         * @param length count values in array
         */
        void addAll(const T* array, uintmax length) {
            uintmax newSize = max(capacity, getSize() + length);
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
            if (index < getSize()) {
                for (uintmax i = index; i < getSize() - 1; i++) {
                    getPointer()[index] = getPointer()[index + 1];
                }
                removeSize(1);
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
            setSize(0, true);
            return true;
        }

        /**
         * Remove unused array's cells in memory
         *
         * @return Does remove unused array's cells in memory
         */
        bool cut() {
            if (getSize() < capacity) {
                resize(getSize());
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
            List<T> result = List<T>(getSize());
            for (uintmax i = 0; i < getSize(); i++) {
                result.add(getPointer()[getSize() - i - 1]);
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
            if (index < getSize()) {
                return getPointer()[index];
            } else {
                throw createException2("List", "Wrong index");
            }
        }

        /**
         * @return count values in list
         */
        uintmax size() const {
            return getSize();
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
            for (int i = 0; i < getSize(); ++i) {
                if (func(getPointer()[i], value)) {
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
            if (size < getSize()) {
                if (removeData) {
                    if (isInStack()) {
                        capacity = size;
                    } else {
                        store.valueWithSize.size = size;
                    }
                    return true;
                } else {
                    return false;
                };
            } else {
                return addSize(size - getSize());
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
            if (getPointer() == nullptr) {
                return nullptr;
            }

            T* array = new T[getSize()];
            memcpy(array, getPointer(), getSize() * sizeof(T));
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
            if (index < getSize()) {
                return getPointer()[index];
            } else {
                throw createException2("List", "Wrong index");
            }
        }
    };

}

#endif //KNIITLIBRARY_LIST_H
