#include "../include/Matrix.h"
#include "../include/Vector.h"


Matrix::Matrix() : container(nullptr), size(0, 0) {}

Matrix::Matrix(double **inputValues, size_t x, size_t y) : size(x, y) {
    if (x == 0 || y == 0) {
        throw std::runtime_error("Some size equals 0.");
    }

    if (inputValues == nullptr) {
        throw std::runtime_error("Not initialized input array");
    }

    container = new Vector[x];
    for (size_t i = 0; i < x; ++i) {
        container[i] = Vector(inputValues[i], y, Row);
    }
}

Matrix::Matrix(const Vector *inputVectors, size_t x, size_t y) : size(x, y) {
    if (x == 0 || y == 0) {
        throw std::runtime_error("Some size equals 0.");
    }

    if (inputVectors == nullptr) {
        throw std::runtime_error("Not initialized input array");
    }

    container = new Vector[x];

    VectorType startType = inputVectors[0].type;

    if (startType == Row) {
        for (size_t i = 0; i < x; ++i) {
            if (inputVectors[i].type != startType) {
                throw std::runtime_error("Input array contains vectors of different types.");
            }
            container[i] = inputVectors[i];
        }

    } else if (startType == Column) {
        *this = Matrix(x, y);
        for (size_t i = 0; i < x; ++i) {
            for (size_t j = 0; j < y; ++j) {
                if (inputVectors[j].type != startType) {
                    throw std::runtime_error("Input array contains vectors of different types.");
                }
                container[i][j] = inputVectors[j][i];
            }
        }
    }
}

Matrix::Matrix(size_t x, size_t y) {
    if (x == 0 || y == 0) {
        throw std::runtime_error("Some size equals 0.");
    }

    container = new Vector[x];
    size = {x, y};
    for (size_t i = 0; i < x; ++i) {
        container[i] = Vector(y, Row);
    }
}

Matrix::Matrix(Matrix&& refMatrix) {
    if (refMatrix.size == std::pair<size_t, size_t>(0, 0)) {
        throw std::runtime_error("Invalid matrix size.");
    }

    if (this != &refMatrix) {
        this->~Matrix();

        size = refMatrix.size;

        container = refMatrix.container;

        refMatrix.container = nullptr;
        refMatrix.size.first = 0;
        refMatrix.size.second = 0;
    }
}


Matrix::Matrix(const Matrix &refMatrix) {
    if (refMatrix.size == std::pair<size_t, size_t>(0, 0)) {
        throw std::runtime_error("Invalid matrix size.");
    }

    if (this != &refMatrix) {
        this->~Matrix();

        size = refMatrix.size;

        container = new Vector[size.first];
        for (size_t i = 0; i < size.first; ++i) {
            container[i] = refMatrix.container[i];
        }
    }
}


Matrix &Matrix::operator=(Matrix&& matrix) noexcept {
    if (this != &matrix) {
        size = matrix.size;
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

        size = matrix.size;

        container = new Vector[size.first];
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

Vector Matrix::getColumn(size_t index) const {
    if (index >= size.second) {
        throw std::runtime_error("Index > size.");
    }

    Vector column(size.first, Column);

    for (size_t i = 0; i < size.first; ++i) {
        column[i] = container[i][index];
    }

    return column;
}

Vector Matrix::getRow(size_t index) const {
    if (index >= size.first) {
        throw std::runtime_error("Index > size.");
    }
    return container[index];
}

Vector Matrix::getDiagonal(bool diagonalChoice) {
    if (size.first != size.second) {
        throw std::runtime_error("Matrix isn't square.");
    }

    Vector result(size.first, Row);

    for (size_t i = 0; i < size.first; ++i) {
        if (diagonalChoice) {
            result[i] = container[i][i];
        }
        else {
            result[i] = container[i][size.second - 1 - i];
        }
    }

    return result;
}

Matrix Matrix::getTransposed() {
    Matrix transposedMatrix(size.second, size.first);

    for (size_t i = 0; i < size.second; ++i) {
        for (size_t j = 0; j < size.first; ++j) {
            transposedMatrix[i][j] = container[j][i];
        }
    }

    return transposedMatrix;
}

double Matrix::getDeterminant() { // По методу Гаусса
    if (size.first != size.second) {
        throw std::runtime_error("Matrix isn't square.");
    }

    double determinant = 1;

    Matrix copy(*this);

    for (size_t i = 0; i < size.second - 1; ++i) {
        for (size_t j = size.first - 2; j != i - 1; j--) {
            double factor = -(copy.container[j + 1][i] / copy.container[j][i]);
            for (size_t k = 0; k < size.second; ++k) {
                copy.container[j + 1][k] += factor * copy.container[j][k];
            }
        }
    }
    for (size_t i = 0; i < size.second; ++i) {
        determinant *= copy.container[i][i];
    }
    return determinant;
}

Matrix Matrix::getUnitMatrix(size_t size) {
    Matrix unitMatrix(size, size);

    for (size_t i = 0; i < size; ++i) {
        unitMatrix[i][i] = 1;
    }

    return unitMatrix;
}

Matrix Matrix::concatenateMatrices(const Matrix &oneMatrix, const Matrix &otherMatrix) {
    if (oneMatrix.size != otherMatrix.size) {
        throw std::runtime_error("Matrices has different sizes.");
    }

    size_t newX = oneMatrix.size.first;
    size_t newY = oneMatrix.size.second + otherMatrix.size.second;

    Matrix result(newX, newY);
    for (size_t i = 0; i < newX; ++i) {
        for (size_t j = 0; j < oneMatrix.size.second; ++j) {
            result[i][j] = oneMatrix.container[i][j];
            result[i][j + oneMatrix.size.second] = otherMatrix.container[i][j];
        }
    }

    return result;
}

Matrix Matrix::getInverseMatrix() {
    if (size.first != size.second) {
        throw std::runtime_error("Matrix isn't square.");
    }

    if (getDeterminant() == 0) {
        throw std::runtime_error("Matrix is degenerate.");
    }

    Matrix inverseMatrix;
    Matrix middleMatrix = concatenateMatrices(getUnitMatrix(size.first), *this);


    for (size_t i = 0; i < middleMatrix.size.first; ++i) {
        middleMatrix[i] *= (1 / middleMatrix[i][i + size.second]);

        for (size_t j = i + 1; j < middleMatrix.size.first; ++j) {
            double factor = -middleMatrix[j][i + size.second];
            middleMatrix[j] += middleMatrix[i] * factor;
        }


        for (size_t j = i; j-- > 0;) {
            double factor = -middleMatrix[j][i + size.second];
            middleMatrix[j] += middleMatrix[i] * factor;
        }
    }

    inverseMatrix = Matrix(middleMatrix.container, size.first, size.second);
    return inverseMatrix;
}

Vector &Matrix::operator[](size_t index) {
    if (index >= size.first) {
        throw std::runtime_error("Index's out of range.");
    }
    return container[index];
}


Matrix &Matrix::operator+=(const Matrix &matrix) {
    if (size != matrix.size) {
        throw std::runtime_error("Matrices has different sizes");
    }

    for (size_t i = 0; i < size.first; ++i) {
        container[i] += matrix.container[i];
    }

    return *this;
}


Matrix Matrix::operator+(const Matrix &matrix) {
    if (size != matrix.size) {
        throw std::runtime_error("Matrices has different sizes");
    }

    Matrix result(container, size.first, size.second);

    result += matrix;

    return result;
}


Matrix &Matrix::operator-=(const Matrix &matrix) {
    if (size != matrix.size) {
        throw std::runtime_error("Matrices has different sizes");
    }

    for (size_t i = 0; i < size.first; ++i) {
        container[i] -= matrix.container[i];
    }

    return *this;
}

Matrix Matrix::operator-(const Matrix &matrix) {
    if (size != matrix.size) {
        throw std::runtime_error("Matrices has different sizes");
    }

    Matrix result(container, size.first, size.second);
    result -= matrix;

    return result;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    if (size != matrix.size) {
        throw std::runtime_error("Matrices has different sizes");
    }

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
    if (size.second != matrix.size.first) {
        throw std::runtime_error("Matrices has wrong sizes");
    }

    Matrix result(size.first, matrix.size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < matrix.size.second; ++j) {
            for (size_t k = 0; k < size.second; ++k) {
                result[i][j] += container[i][k] * matrix.container[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator*(const Vector &vector) {
    Matrix matrixWrap;
    if (vector.type == Row) {
        if (size.second != 1) {
            throw std::runtime_error("Matrices has wrong sizes");
        }
        matrixWrap = Matrix(&vector, 1, vector.getLength());
    } else if (vector.type == Column) {
        if (size.second != vector.getLength()) {
            throw std::runtime_error("Matrices has wrong sizes");
        }
        matrixWrap = Matrix(&vector, vector.getLength(), 1);
    }

    return *this * matrixWrap;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.size.first; ++i) {
        for (size_t j = 0; j < matrix.size.second; ++j) {
            os << matrix.container[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}
