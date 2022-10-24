//
// Created by Pavel on 22.10.2022.
//

#ifndef MATRIX_VECTORROW_H
#define MATRIX_VECTORROW_H

#include "Vector.h"

class Matrix;

class VectorColumn;

class VectorRow : public Vector {
public:
    VectorRow();
    VectorRow(const VectorRow &refVector);
    VectorRow(const double *inputNumbers, size_t size);

    ~VectorRow() = default;

    VectorRow &operator=(VectorRow&& row) noexcept;
    VectorRow &operator=(const VectorRow& row) noexcept;

    VectorRow &operator+=(const VectorRow& vector);
    VectorRow operator+(const VectorRow& vector);
    VectorRow &operator-=(const VectorRow& vector);
    VectorRow operator-(const VectorRow& vector);

    VectorRow &operator*=(const VectorRow& vector);
    VectorRow &operator*=(double number);
    Matrix operator*(const Matrix &matrix);

    bool operator==(const VectorRow &vectorToCompare) const;
    bool operator!=(const VectorRow &vectorToCompare) const;

    VectorColumn getTransposed();

    void printVector() override;
};

#endif //MATRIX_VECTORROW_H
