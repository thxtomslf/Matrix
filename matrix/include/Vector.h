#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H


class Matrix;


enum VectorType {
    Row,
    Column
};


class Vector {
private:
    double *container = nullptr;
    size_t length;
public:
    VectorType type;

    Vector();
    Vector(const Vector &refVector);
    Vector(Vector&& refVector);
    Vector(const double *inputNumbers, size_t size, VectorType type);
    Vector(size_t size, VectorType type);

    ~Vector();

    Vector &operator=(Vector&& row) noexcept;
    Vector &operator=(const Vector& row) noexcept;

    Vector &operator+=(const Vector& vector);
    Vector operator+(const Vector& vector);
    Vector &operator-=(const Vector& vector);
    Vector operator-(const Vector& vector);

    Vector &operator*=(const Vector& vector);
    Vector &operator*=(double number);
    Vector operator*(double number);
    Matrix operator*(const Matrix &matrix);

    bool operator==(const Vector &vectorToCompare) const;
    bool operator!=(const Vector &vectorToCompare) const;

    double &operator[](size_t index) const;

    Vector getTransposed();

    size_t getLength() const;

    void printVector();

};

#endif //MATRIX_VECTOR_H
