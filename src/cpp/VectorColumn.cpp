//
// Created by Pavel on 22.10.2022.
//
#include <cstddef>
#include <iostream>
#include <cassert>

#include "../include/Matrix.h"
#include "../include/VectorColumn.h"


VectorColumn::VectorColumn() : Vector() {}

VectorColumn::VectorColumn(const VectorColumn &refVector) : Vector(refVector.container, refVector.length){}

VectorColumn::VectorColumn(const double *inputNumbers, size_t size) : Vector(inputNumbers, size) {}

VectorColumn &VectorColumn::operator=(VectorColumn &&column) noexcept {
    if (this != &column) {
        this->~VectorColumn();

        length = column.length;
        container = column.container;

        column.container = nullptr;
        column.length = 0;
    }
    return *this;
}

VectorColumn &VectorColumn::operator=(const VectorColumn &column) noexcept {
    if (this != &column) {
        this->~VectorColumn();

        length = column.length;
        container = new double[length];

        for (size_t i = 0; i < length; ++i) {
            container[i] = column.container[i];
        }
    }
    return *this;
}

VectorColumn &VectorColumn::operator+=(const VectorColumn& vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] += vector.container[i];
    }

    return *this;
}

VectorColumn VectorColumn::operator+(const VectorColumn &vector) {
    assert(length == vector.length);

    VectorColumn result(container, length);
    result += vector;

    return result;
}

VectorColumn &VectorColumn::operator-=(const VectorColumn &vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] -= vector.container[i];
    }

    return *this;
}

VectorColumn VectorColumn::operator-(const VectorColumn &vector) {
    assert(length == vector.length);

    VectorColumn result(container, length);
    result -= vector;

    return result;
}

VectorColumn &VectorColumn::operator*=(const VectorColumn &vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] *= vector.container[i];
    }

    return *this;
}

VectorColumn &VectorColumn::operator*=(double number) {
    for (size_t i = 0; i < length; ++i) {
        container[i] *= number;
    }
    return *this;
}

Matrix VectorColumn::operator*(const Matrix &matrix) {
    Matrix matrixWrap(this, length, 1);

    return matrixWrap * matrix;
}

bool VectorColumn::operator==(const VectorColumn &vectorToCompare) const {
    if (length == vectorToCompare.length) {
        for (size_t i = 0; i < length; ++i) {
            if (container[i] != vectorToCompare.container[i]) return false;
        }
        return true;
    }
    return false;
}

bool VectorColumn::operator!=(const VectorColumn &vectorToCompare) const {
    return !(*this == vectorToCompare);
}


VectorRow VectorColumn::getTransposed() {
    return VectorRow(container, length);
}

void VectorColumn::printVector() {
    for (size_t i = 0; i < length; ++i) {
        std::cout << "[" << container[i] << "]\n";
    }
}











