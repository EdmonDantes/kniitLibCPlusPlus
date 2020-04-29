//
// Created by masa_ on 12.04.2020.
//

#include "../datatype.h"

KNIIT_LIB_NAMESPACE {
DataType::DataType(int id, bool simple) {
    this->id = id;
    this->simple = simple;
}

DataType::DataType(const DataType & type) {
    this->id = type.id;
    this->simple = type.simple;
}
bool DataType::operator==(const DataType & type) {
    return id == type.id;
}
bool DataType::isSimple() {
    return simple;
}
}


