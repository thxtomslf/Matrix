//
// Created by Pavel on 21.10.2022.
//

#include <iostream>
#include <cassert>
#include "../include/Matrix.h"


Matrix::Matrix() {
    container = nullptr;
    size.first = 0;
    size.second = 0;
}

Matrix::Matrix(double **inputValues, size_t x, size_t y) : size(x, y) {
    container = new VectorRow[x];

    for (size_t i = 0; i < x; ++i) {
        container[i] = VectorRow(inputValues[i], y);
    }
}

Matrix::Matrix(const VectorRow *inputRows, size_t x, size_t y) : size(x, y) {
    container = new VectorRow[x];

    for (size_t i = 0; i < x; ++i) {
        container[i] = inputRows[i];
    }
}

Matrix::Matrix(const VectorColumn *inputColumn, size_t x, size_t y) : size(x, y) {
    container = new VectorRow[x];

    for (size_t i = 0; i < x; ++i) {
        double *row = new double[size.second];
        for (size_t j = 0; j < y; ++j) {
            auto a = inputColumn[j][i];
            row[j] =  inputColumn[j][i];
        }
        container[i] = VectorRow(row, size.second);
        delete[] row;
    }
}

Matrix &Matrix::operator=(Matrix &&matrix) noexcept {
    if (this != &matrix) {

        size.first = matrix.size.first;
        size.second = matrix.size.second;
        container = matrix.container;

        matrix.container = nullptr;
        matrix.size.first = 0;
        matrix.size.second = 0;
    }
    return *this;
}


Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this != &matrix) {
        this->~Matrix();

        size.first = matrix.size.first;
        size.second = matrix.size.second;

        container = new VectorRow[size.first];
        for (size_t i = 0; i < size.first; ++i) {
            container[i] = matrix.container[i];
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix &matrix) const {
    if (size.first != matrix.size.first || size.second != matrix.size.second) {
        return false;
    }

    for (size_t i = 0; i < size.first; ++i) {
        if (this->getRow(i) != matrix.getRow(i)) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &matrix) const {
    return !(*this == matrix);
}

Matrix::~Matrix() {
    delete[] container;
}

VectorColumn Matrix::getColumn(size_t index) const {
    assert(index < size.second);

    double *columnValues = new double[size.first];

    for (size_t i = 0; i < size.first; ++i) {
        columnValues[i] = container[i][index];
    }

    VectorColumn column(columnValues, size.first);
    delete[] columnValues;
    return column;
}

VectorRow Matrix::getRow(size_t index) const {
    assert(index < size.first);
    return container[index];
}

VectorRow Matrix::getDiagonal(bool diagonalChoice) {
    assert(size.first == size.second);
    double *diagonalValues = new double[size.first];

    for (size_t i = 0; i < size.first; ++i) {
        if (diagonalChoice) diagonalValues[i] = container[i][i];
        else diagonalValues[i] = container[i][size.second - 1 - i];
    }
    VectorRow result(diagonalValues, size.first);
    delete[] diagonalValues;

    return result;
}

Matrix Matrix::getTransposed() {
    auto *columns = new VectorColumn[size.first];

    for (size_t i = 0; i < size.first; ++i) {
        columns[i] = container[i].getTransposed();
    }
    Matrix transposedMatrix(columns, size.second, size.first);
    delete[] columns;

    return transposedMatrix;
}

double Matrix::getDeterminant() { // По методу Гаусса
    assert(size.first == size.second);

    double determinant = 1;

    for (size_t i = 0; i < size.second - 1; ++i) {
        for (size_t j = size.first - 2; j != i - 1; j--) {
            double factor = -(container[j + 1][i] / container[j][i]);
            for (size_t k = 0; k < size.second; ++k) {
                container[j + 1][k] += factor * container[j][k];
            }
        }
    }
    for (size_t i = 0; i < size.second; ++i) {
        determinant *= container[i][i];
    }
    return determinant;
}


VectorRow &Matrix::operator[](size_t index) {
    assert(index < size.first);
    return container[index];
}


Matrix &Matrix::operator+=(const Matrix &matrix) {
    assert(size.first == matrix.size.first && size.second == matrix.size.second);

    for (size_t i = 0; i < size.first; ++i) {
        container[i] += matrix.container[i];
    }

    return *this;
}


Matrix Matrix::operator+(const Matrix &matrix) {
    assert(size.first == matrix.size.first && size.second == matrix.size.second);
    Matrix result(container, size.first, size.second);

    result += matrix;

    return result;
}


Matrix &Matrix::operator-=(const Matrix &matrix) {
    assert(size.first == matrix.size.first && size.second == matrix.size.second);

    for (size_t i = 0; i < size.first; ++i) {
        container[i] -= matrix.container[i];
    }

    return *this;
}

Matrix Matrix::operator-(const Matrix &matrix) {
    assert(size.first == matrix.size.first && size.second == matrix.size.second);

    Matrix result(container, size.first, size.second);
    result -= matrix;

    return result;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    assert(size.first == matrix.size.first && size.second == matrix.size.second);

    for (size_t i = 0; i < size.first; ++i) {
        container[i] *= matrix.container[i];
    }

    return *this;
}


Matrix &Matrix::operator*=(double number) {
    for (size_t i = 0; i < size.first; ++i) {
        container[i] *= number;
    }
    return *this;
}


Matrix Matrix::operator*(const Matrix &matrix) {
    assert(size.second == matrix.size.first);

    VectorRow *resultContainer = new VectorRow[size.first]; // Инициализация контейнера для результирующей матрицы

    for (size_t i = 0; i < size.first; ++i) {

        auto *rowValues = new double[matrix.size.second];
        for (size_t j = 0; j < matrix.size.second; ++j) {  // Заполнение результирующей матрицы начальными значениями
            rowValues[j] = 0.0;
        }
        resultContainer[i] = VectorRow(rowValues, matrix.size.second);
        delete[] rowValues;

        for (size_t j = 0; j < matrix.size.second; ++j) {

            for (size_t k = 0; k < size.second; ++k) {
                resultContainer[i][j] += container[i][k] * matrix.container[k][j];
            }
        }
    }

    Matrix result(resultContainer, size.first, matrix.size.second);
    delete[] resultContainer;

    return result;
}

Matrix Matrix::operator*(const VectorRow &row) {
    Matrix matrixWrap(&row, 1, row.getLength());

    return *this * matrixWrap;
}

Matrix Matrix::operator*(const VectorColumn &column) {
    Matrix matrixWrap(&column, column.getLength(), 1);

    return *this * matrixWrap;
}

void Matrix::printMatrix() {
    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            std::cout << container[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::pair<size_t, size_t> Matrix::getSize() {
    return size;
}




