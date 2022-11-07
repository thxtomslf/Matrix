#ifndef MATRIX_INCLUDE_VECTOR_H_
#define MATRIX_INCLUDE_VECTOR_H_


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

    Vector &operator=(Vector&& otherVector);
    Vector &operator=(const Vector& otherVector);

    Vector &operator+=(const Vector& otherVector);
    Vector operator+(const Vector& otherVector);
    Vector &operator-=(const Vector& otherVector);
    Vector operator-(const Vector& otherVector);

    Vector &operator*=(const Vector& otherVector);
    Vector &operator*=(double number);
    Vector operator*(double number);
    Matrix operator*(const Matrix &matrix);

    bool operator==(const Vector &vectorToCompare) const;
    bool operator!=(const Vector &vectorToCompare) const;

    double &operator[](size_t index) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

    Vector getTransposed();

    size_t getLength() const;
};

#endif  // MATRIX_INCLUDE_VECTOR_H_
