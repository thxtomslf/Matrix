//
// Created by Pavel on 21.10.2022.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <utility>

#include "VectorRow.h"
#include "VectorColumn.h"


class Matrix {
    VectorRow *container;
    std::pair<size_t, size_t> size;
public:
    Matrix();
    Matrix(Matrix &&refMatrix) = default;
    Matrix(const Matrix &refMatrix) = default;
    explicit Matrix(double **inputValues, size_t x, size_t y);
    explicit Matrix(const VectorRow *inputRows, size_t x, size_t y);
    explicit Matrix(const VectorColumn *inputColumn, size_t x, size_t y);

    ~Matrix();

    VectorColumn getColumn(size_t index) const;
    VectorRow getRow(size_t index) const;
    VectorRow getDiagonal(bool diagonalChoice);
    Matrix getTransposed();
    double getDeterminant();

    Matrix &operator=(Matrix&& matrix) noexcept;
    Matrix &operator=(const Matrix& matrix);

    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    VectorRow &operator[](size_t index);

    Matrix &operator+=(const Matrix &matrix);
    Matrix operator+(const Matrix &matrix);
    Matrix &operator-=(const Matrix &matrix);
    Matrix operator-(const Matrix &matrix);

    Matrix &operator*=(const Matrix &matrix);
    Matrix &operator*=(double number);

    Matrix operator*(const Matrix &matrix);
    Matrix operator*(const VectorRow &row);
    Matrix operator*(const VectorColumn &column);

    std::pair<size_t, size_t> getSize();
    void printMatrix();
};

#endif //MATRIX_MATRIX_H
