#include "gtest/gtest.h"

#include "../include/Matrix.h"
#include "../include/Vector.h"

// 4) умножение числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу
class FourthPointTest : public ::testing::Test {
protected:
    Matrix matrix;
    Matrix matrixMultipliedByDouble;
    double factor = 10;

    Vector row;
    Matrix rowAndMatrixMultiplied;

    double **values = new double*[2];
    double **valuesMultipliedByDouble = new double*[2];

    double *rowValues = new double[2] {100, 200};
    double **resultValuesOfRowAndMatrixMultiplication = new double*[1];

    void SetUp() override {
        values[0] = new double[4] {13, 20, 15, 9};
        values[1] = new double[4] {0, 3, 12, 13};

        valuesMultipliedByDouble[0] = new double[4] {values[0][0] * factor, values[0][1] * factor, values[0][2] * factor, values[0][3] * factor};
        valuesMultipliedByDouble[1] = new double[4] {values[1][0] * factor, values[1][1] * factor, values[1][2] * factor, values[1][3] * factor};

        matrix = Matrix(values, 2, 4);
        matrixMultipliedByDouble = Matrix(valuesMultipliedByDouble, 2, 4);

        row = Vector(rowValues, 2, Row);

        resultValuesOfRowAndMatrixMultiplication[0] = new double[4] {rowValues[0] * values[0][0] + rowValues[1] * values[1][0],
                                                                     rowValues[0] * values[0][1] + rowValues[1] * values[1][1],
                                                                     rowValues[0] * values[0][2] + rowValues[1] * values[1][2],
                                                                     rowValues[0] * values[0][3] + rowValues[1] * values[1][3]};
        rowAndMatrixMultiplied = Matrix(resultValuesOfRowAndMatrixMultiplication, 1, 4);

    }

    void TearDown() override {
        delete[] values[0];
        delete[] values[1];

        delete[] valuesMultipliedByDouble[0];
        delete[] valuesMultipliedByDouble[1];

        delete[] resultValuesOfRowAndMatrixMultiplication;

        delete[] values;
        delete[] valuesMultipliedByDouble;
    }
};

TEST_F(FourthPointTest, MatrixAndDoubleMultiply) {
    std::cout << "Test: MatrixAndDoubleMultiply\n";
    std::cout << "Factor: " << factor << "\n";
    std::cout << "Matrix: " << "\n";
    std::cout << matrix;
    std::cout << "Result: " << "\n";
    matrix *= factor;
    std::cout << matrix;
    EXPECT_EQ(matrix, matrixMultipliedByDouble);
    std::cout << "\n";
}


TEST_F(FourthPointTest, RowAndMatrixMultiply) {
    std::cout << "Test: RowAndMatrixMultiply\n";
    std::cout << "Row: ";
    std::cout << row;
    std::cout << "\n";
    std::cout << "Matrix: " << "\n";
    std::cout << matrix;
    std::cout << "Result: " << "\n";
    std::cout << (row * matrix);
    EXPECT_EQ(row * matrix, rowAndMatrixMultiplied);
    std::cout << "\n";
}

TEST_F(FourthPointTest, MatrixAndRowMultiply) {
    std::cout << "Test: MatrixAndRowMultiply\n";
    std::cout << "Row: ";
    std::cout << row;
    std::cout << "\n";
    std::cout << "Matrix: " << "\n";
    matrix = Matrix(values, 2, 1);
    std::cout << matrix;
    std::cout << "Result: " << "\n";
    std::cout << (matrix * row);
    double **resultValues = new double*[2];
    resultValues[0] = new double[2] {1300, 2600};
    resultValues[1] = new double[2] {0, 0};
    EXPECT_EQ(matrix * row, Matrix(resultValues, 2, 2));
    std::cout << "\n";

    delete[] resultValues[0];
    delete[] resultValues[1];
    delete[] resultValues;
}

TEST_F(FourthPointTest, MatrixAndMatrixMultiply) {
    std::cout << "Test: MatrixAndMatrixMultiply\n";
    std::cout << "MatrixA:\n";
    Vector col = matrix.getRow(0).getTransposed();
    Matrix matrixA(&col, 4, 1);
    std::cout << matrixA;
    std::cout << "MatrixB: " << "\n";
    auto *columns = new Vector[4];
    columns[0] = matrix.getRow(0).getTransposed();
    columns[1] = matrix.getRow(1).getTransposed();
    columns[2] = matrix.getRow(0).getTransposed();
    columns[3] = matrix.getRow(1).getTransposed();
    Matrix matrixB(columns, 4, 4);
    std::cout << matrixB;
    std::cout << "Result: " << "\n";
    std::cout << (matrixB * matrixA);
    std::cout << "\n";

    double **resultValues = new double*[4];
    resultValues[0] = new double[1] {matrixB[0][0] * matrixA[0][0] +
                                     matrixB[0][1] * matrixA[1][0] +
                                     matrixB[0][2] * matrixA[2][0] +
                                     matrixB[0][3] * matrixA[3][0]};

    resultValues[1] = new double[1] {matrixB[1][0] * matrixA[0][0] +
                                     matrixB[1][1] * matrixA[1][0] +
                                     matrixB[1][2] * matrixA[2][0] +
                                     matrixB[1][3] * matrixA[3][0]};

    resultValues[2] = new double[1] {matrixB[2][0] * matrixA[0][0] +
                                     matrixB[2][1] * matrixA[1][0] +
                                     matrixB[2][2] * matrixA[2][0] +
                                     matrixB[2][3] * matrixA[3][0]};

    resultValues[3] = new double[1] {matrixB[3][0] * matrixA[0][0] +
                                     matrixB[3][1] * matrixA[1][0] +
                                     matrixB[3][2] * matrixA[2][0] +
                                     matrixB[3][3] * matrixA[3][0]};
    Matrix result(resultValues, 4, 1);

    EXPECT_EQ(matrixB * matrixA, result);

    for (size_t i = 0; i < 4; ++i) {
        delete[] resultValues[i];
    }

    delete[] columns;
    delete[] resultValues;

}

TEST_F(FourthPointTest, ColumnAndMatrixMultiply) {
    std::cout << "Test: ColumnAndMatrixMultiply\n";
    std::cout << "Column:\n";
    auto column = row.getTransposed();
    std::cout << column;
    std::cout << "\n";

    std::cout << "Matrix: " << "\n";
    matrix = Matrix(values, 1, 2);
    std::cout << matrix;

    std::cout << "Result: " << "\n";
    std::cout << (column * matrix);

    double **resultValues = new double*[2];
    resultValues[0] = new double[2] {column[0] * matrix[0][0],
                                     column[0] * matrix[0][1]};

    resultValues[1] = new double[2] {column[1] * matrix[0][0],
                                     column[1] * matrix[0][1]};

    Matrix result(resultValues, 2, 2);

    EXPECT_EQ(column * matrix, result);

    delete[] resultValues[0];
    delete[] resultValues[1];
    delete[] resultValues;
}
