#include "../include/Matrix.h"
#include "../include/Vector.h"


Vector::Vector() : container(nullptr), length(0), type(Row) {}

Vector::Vector(const Vector &refVector) {
    if (this != &refVector) {
        this->~Vector();

        *this = Vector(refVector.container, refVector.length, refVector.type);
    }
}

Vector::Vector(const double *inputNumbers, size_t size, VectorType type) : length(size), type(type) {
    if (size == 0) {
        throw std::runtime_error("Invalid vector size.");
    }

    container = new double[size];
    if (inputNumbers != nullptr) {
        for (size_t i = 0; i < size; ++i) {
            container[i] = inputNumbers[i];
        }
    } else {
        for (size_t i = 0; i < size; ++i) {
            container[i] = 0;
        }
    }
}

Vector::Vector(Vector&& refVector) {
    if (this != &refVector) {
        this->~Vector();

        container = refVector.container;
        length = refVector.length;
        type = refVector.type;

        refVector.container = nullptr;
        refVector.length = 0;
    }
}

Vector::Vector(size_t size, VectorType type) {
    if (size == 0) {
        throw std::runtime_error("Invalid vector size.");
    }

    container = new double[size];
    length = size;
    this->type = type;
    for (size_t i = 0; i < size; ++i) {
        container[i] = 0;
    }
}

Vector::~Vector() {
    delete[] container;
    length = 0;
}

Vector &Vector::operator=(Vector&& otherVector) {
    if (otherVector.length == 0) {
        throw std::runtime_error("Invalid vector size.");
    }

    if (this != &otherVector) {
        this->~Vector();

        length = otherVector.length;
        container = otherVector.container;
        type = otherVector.type;

        otherVector.container = nullptr;
        otherVector.length = 0;
    }
    return *this;
}


Vector &Vector::operator=(const Vector &otherVector) {
    if (otherVector.length == 0) {
        throw std::runtime_error("Invalid vector size.");
    }

    if (this != &otherVector) {
        this->~Vector();

        length = otherVector.length;
        container = new double[length];
        type = otherVector.type;

        for (size_t i = 0; i < length; ++i) {
            container[i] = otherVector.container[i];
        }
    }
    return *this;
}

Vector &Vector::operator+=(const Vector &otherVector) {
    if (otherVector.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (otherVector.length != length) {
        throw std::runtime_error("Vectors' lengths are different.");
    }
    for (size_t i = 0; i < length; ++i) {
        container[i] += otherVector.container[i];
    }

    return *this;
}

Vector Vector::operator+(const Vector &otherVector) {
    if (otherVector.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (otherVector.length != length) {
        throw std::runtime_error("Vectors' lengths are different.");
    }
    Vector result(container, length, type);
    result += otherVector;

    return result;
}

Vector &Vector::operator-=(const Vector &otherVector) {
    if (otherVector.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (otherVector.length != length) {
        throw std::runtime_error("Vectors' lengths are different.");
    }
    for (size_t i = 0; i < length; ++i) {
        container[i] -= otherVector.container[i];
    }

    return *this;
}

Vector Vector::operator-(const Vector &otherVector) {
    if (otherVector.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (otherVector.length != length) {
        throw std::runtime_error("Vectors' lengths are different.");
    }
    Vector result(container, length, type);
    result -= otherVector;

    return result;
}

Vector &Vector::operator*=(const Vector &otherVector) {
    if (otherVector.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (otherVector.length != length) {
        throw std::runtime_error("Vectors' lengths are different.");
    }
    for (size_t i = 0; i < length; ++i) {
        container[i] *= otherVector.container[i];
    }

    return *this;
}

Vector &Vector::operator*=(double number) {
    for (size_t i = 0; i < length; ++i) {
        container[i] *= number;
    }

    return *this;
}

Vector Vector::operator*(double number) {
    Vector multiplied(*this);

    for (size_t i = 0; i < length; ++i) {
        multiplied.container[i] *= number;
    }

    return multiplied;
}

Matrix Vector::operator*(const Matrix &matrix) {
    Matrix matrixWrap;
    if (type == Row) {
        matrixWrap = Matrix(this, 1, length);
    } else if (type == Column) {
        matrixWrap = Matrix(this, length, 1);
    }

    return matrixWrap * matrix;
}

bool Vector::operator==(const Vector &vectorToCompare) const {
    if (vectorToCompare.type != type) {
        throw std::runtime_error("Vectors' types are different.");
    }

    if (length == vectorToCompare.length) {
        for (size_t i = 0; i < length; ++i) {
            if (std::abs(container[i] - vectorToCompare.container[i]) > 1e-6) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Vector::operator!=(const Vector &vectorToCompare) const {
    return !(*this == vectorToCompare);
}

double &Vector::operator[](size_t index) const {
    if (index >= length) {
        throw std::runtime_error("Index >= vector length.");
    }
    return container[index];
}

Vector Vector::getTransposed() {
    return Vector(container, length, type == Row ? Column : Row);
}

size_t Vector::getLength() const {
    return length;
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    if (vector.type == Row) {
        os << "[";
        for (size_t i = 0; i < vector.length; ++i) {
            os << vector.container[i] << ", ";
        }
        os << ']';
    } else if (vector.type == Column) {
        for (size_t i = 0; i < vector.length; ++i) {
            os << "[" << vector.container[i] << "]\n";
        }
    }
    return os;
}
