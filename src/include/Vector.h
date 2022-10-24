//
// Created by Pavel on 22.10.2022.
//

#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <cstddef>

class Vector {
protected:
    double *container{};
    size_t length{};

    Vector() = default;
    Vector(const double *inputNumbers, size_t size);
public:
    ~Vector();
    virtual size_t getLength() const;

    virtual double &operator[](size_t index) const;
    virtual void printVector() = 0;
};


#endif //MATRIX_VECTOR_H
