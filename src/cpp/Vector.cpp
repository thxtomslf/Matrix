//
// Created by Pavel on 22.10.2022.
//


#include <cassert>
#include "../include/Vector.h"


Vector::Vector(const double *inputNumbers, size_t size) : length(size) {
    container = new double[size];
    for (size_t i = 0; i < size; ++i) {
        container[i] = inputNumbers[i];
    }
}

double &Vector::operator[](size_t index) const {
    assert(index < length);
    return container[index];
}

Vector::~Vector() {
    delete[] container;
}

size_t Vector::getLength() const {
    return length;
}


