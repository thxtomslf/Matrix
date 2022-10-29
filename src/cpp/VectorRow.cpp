//
// Created by Pavel on 22.10.2022.
//

#include <iostream>
#include <cstddef>
#include <cassert>

#include "../include/Matrix.h"
#include "../include/VectorRow.h"


VectorRow::VectorRow() : Vector() {}

VectorRow::VectorRow(const VectorRow &refVector) : Vector(refVector.container, refVector.length) {}

VectorRow::VectorRow(const double *inputNumbers, size_t size) : Vector(inputNumbers, size) {}

VectorRow &VectorRow::operator=(VectorRow&& row) noexcept {
    if (this != &row) {
        this->~VectorRow();

        length = row.length;
        container = row.container;

        row.container = nullptr;
        row.length = 0;
    }
    return *this;
}


VectorRow &VectorRow::operator=(const VectorRow &row) noexcept {
    if (this != &row) {
        this->~VectorRow();

        length = row.length;
        container = new double[length];

        for (size_t i = 0; i < length; ++i) {
            container[i] = row.container[i];
        }

    }
    return *this;
}

VectorRow &VectorRow::operator+=(const VectorRow &vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] += vector.container[i];
    }

    return *this;
}

VectorRow VectorRow::operator+(const VectorRow &vector) {
    assert(length == vector.length);

    VectorRow result(container, length);
    result += vector;

    return result;
}

VectorRow &VectorRow::operator-=(const VectorRow &vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] -= vector.container[i];
    }

    return *this;
}

VectorRow VectorRow::operator-(const VectorRow &vector) {
    assert(length == vector.length);

    VectorRow result(container, length);
    result -= vector;

    return result;
}

VectorRow &VectorRow::operator*=(const VectorRow &vector) {
    assert(length == vector.length);

    for (size_t i = 0; i < length; ++i) {
        container[i] *= vector.container[i];
    }

    return *this;
}

VectorRow &VectorRow::operator*=(double number) {
    for (size_t i = 0; i < length; ++i) {
        container[i] *= number;
    }

    return *this;
}

Matrix VectorRow::operator*(const Matrix &matrix) {
    Matrix matrixWrap(this, 1, length);

    return matrixWrap * matrix;
}

bool VectorRow::operator==(const VectorRow &vectorToCompare) const {
    if (length == vectorToCompare.length) {
        for (size_t i = 0; i < length; ++i) {
            if (container[i] != vectorToCompare.container[i]) return false;
        }
        return true;
    }
    return false;
}

bool VectorRow::operator!=(const VectorRow &vectorToCompare) const {
    return !(*this == vectorToCompare);
}

VectorColumn VectorRow::getTransposed() {
    return VectorColumn(container, length);
}

void VectorRow::printVector() {
    std::cout << "[";
    for (size_t i = 0; i < length; ++i) {
        std::cout << container[i] << ", ";
    }
    std::cout << ']';
}














