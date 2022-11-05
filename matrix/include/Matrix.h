#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <cassert>

class Vector;

class Matrix {
private:
    Vector *container = nullptr;
    std::pair<size_t, size_t> size;
public:
    Matrix();
    Matrix(Matrix&& refMatrix);
    Matrix(const Matrix &refMatrix);
    explicit Matrix(double **inputValues, size_t x, size_t y);
    explicit Matrix(const Vector *inputVectors, size_t x, size_t y);
    explicit Matrix(size_t x, size_t y);

    ~Matrix();

    Vector getColumn(size_t index) const;
    Vector getRow(size_t index) const;
    Vector getDiagonal(bool diagonalChoice);
    Matrix getTransposed();
    Matrix getInverseMatrix();
    double getDeterminant();
    static Matrix getUnitMatrix(size_t size);
    static Matrix concatenateMatrices(const Matrix &oneMatrix, const Matrix &otherMatrix);

    Matrix &operator=(Matrix&& matrix) noexcept;
    Matrix &operator=(const Matrix& matrix);

    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    Vector &operator[](size_t index);

    Matrix &operator+=(const Matrix &matrix);
    Matrix operator+(const Matrix &matrix);
    Matrix &operator-=(const Matrix &matrix);
    Matrix operator-(const Matrix &matrix);

    Matrix &operator*=(const Matrix &matrix);
    Matrix &operator*=(double number);

    Matrix operator*(const Matrix &matrix);
    Matrix operator*(const Vector &row);

    std::pair<size_t, size_t> getSize();
    void printMatrix();
};

#endif //MATRIX_MATRIX_H
