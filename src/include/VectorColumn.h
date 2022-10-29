//
// Created by Pavel on 22.10.2022.
//

#ifndef MATRIX_VECTORCOLUMN_H
#define MATRIX_VECTORCOLUMN_H


#include "Vector.h"

class Matrix;

class VectorRow;

class VectorColumn : public Vector {
public:
    VectorColumn();
    VectorColumn(const VectorColumn &refVector);
    VectorColumn(const double *inputNumbers, size_t size);

    ~VectorColumn() = default;

    VectorColumn &operator=(VectorColumn&& row) noexcept;
    VectorColumn &operator=(const VectorColumn& row) noexcept;

    VectorColumn &operator+=(const VectorColumn& vector);
    VectorColumn operator+(const VectorColumn& vector);
    VectorColumn &operator-=(const VectorColumn& vector);
    VectorColumn operator-(const VectorColumn& vector);

    VectorColumn &operator*=(const VectorColumn& vector);
    VectorColumn &operator*=(double number);
    Matrix operator*(const Matrix &matrix);

    bool operator==(const VectorColumn &vectorToCompare) const;
    bool operator!=(const VectorColumn &vectorToCompare) const;

    VectorRow getTransposed();
    void printVector() override;
};

#endif //MATRIX_VECTORCOLUMN_H
