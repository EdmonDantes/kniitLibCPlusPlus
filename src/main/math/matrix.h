/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

/**
 * Custom implementation matrix template
 */

#ifndef KNIITLIBRARY_MATRIX_H
#define KNIITLIBRARY_MATRIX_H

#include "../core/core.h"
#include "../collections/list.h"

KNIIT_LIB_NAMESPACE {
    template <class T>
    KNIIT_LIB_CLASS MutableMatrix {
    private:
        List<List<T>> values;
    public:

        MutableMatrix(){}

        MutableMatrix(MutableMatrix&& matrix) {
            this->values = matrix.values;
        }

        uintmax lines(uintmax columnIndex = 0) {
            int count = 0;
            for (uintmax i = 0; i < values.size(); i++) {
                if (values[i].size() > columnIndex) {
                    count++;
                }
            }
            return count;
        }

        uintmax columns(uintmax lineIndex = 0) {
            return lineIndex < values.size() ? values[lineIndex].size() : 0;
        }

        uintmax minLines() {
            int count = 0;
            for (uintmax i = 0; i < values.size(); i++) {
                if (values[i].size() > 0) {
                    count++;
                }
            }

            return count;
        }

        uintmax maxLines() {
            return values.size();
        }

        uintmax minColumns() {
            uintmax minIndex = 0;
            for (uintmax i = 0; i < values.size(); i++) {
                if (values[i].size() < values[minIndex].size()) {
                    minIndex = i;
                }
            }
            return minIndex < values.size() ? values[minIndex].size() : 0;
        }

        uintmax maxColumns() {
            uintmax maxSize = 0;
            for (uintmax i = 0; i < values.size(); i++) {
                if (values[i].size() > maxSize) {
                    maxSize = values[i].size();
                }
            }
            return maxSize;
        }

        bool isSquare() {
            uintmax _maxLines = maxLines();
            uintmax _maxColumns = maxColumns();
            return _maxLines == minLines() && _maxColumns == minColumns() && _maxColumns == _maxLines;
        }

        MutableMatrix<T>& getSubMatrix(uintmax x, uintmax y, uintmax lines, uintmax columns);

        bool addLine(List<T>& line) {
            values.add(line);
            return true;
        }

        bool addColumn(List<T>& column) {
            for (uintmax i = 0; i < column.size(); i++) {
                while (values.size() <= i) {
                    values.add(List<T>());
                }
                values.get(i).add(column.get(i));
            }
            return true;
        }

        List<T>& removeLine(uintmax index) {
            if (index >= values.size()) {
                return List<T>();
            }

            List<T>& tmp = getLine(index);
            values.remove(index);
            return tmp;
        }

        List<T>& removeColumn(uintmax index);

        List<T>& getLine(uintmax index) {
            if (index < values.size()) {
                return values.get(index);
            }
            return std::move(List<T>());
        }

        List<T>& getColumn(uintmax index) {
            List<T> result(maxColumns());
            for (uintmax i = 0; i < values.size(); i++) {
                if (index < values[i].size()) {
                    result.add(values[i][index]);
                }
            }
            return result;
        }
    };
};


#endif //KNIITLIBRARY_MATRIX_H
