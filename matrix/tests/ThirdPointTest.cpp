#include "gtest/gtest.h"

#include "../include/Matrix.h"
#include "../include/Vector.h"


// 3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности
class ThirdPointTest : public ::testing::Test {
protected:
    Matrix matrix1;
    Matrix matrix2;
    Matrix matrix3;

    Matrix matrix1_2_multiplied;
    Matrix matrix1_2_summed;
    Matrix matrix1_2_subtract;

    Vector row1;
    Vector row2;
    Vector row3;

    Vector row1_2_multiplied;
    Vector row1_2_summed;
    Vector row1_2_subtract;

    Vector col1;
    Vector col2;
    Vector col3;

    Vector col1_2_multiplied;
    Vector col1_2_summed;
    Vector col1_2_subtract;

    double **values1 = new double*[2];
    double **values2 = new double*[2];

    double **values1_2_multiplied = new double*[2];
    double **values1_2_summed = new double*[2];
    double **values1_2_subtract = new double*[2];

    void SetUp() override {
        values1[0] = new double[4] {13, 20, 15, 9};
        values1[1] = new double[4] {0, 3, 12, 13};

        values2[0] = new double[4] {2, 2, 2, 2};
        values2[1] = new double[4] {-1, -1, -1, -1};


        values1_2_multiplied[0] = new double[4] {26, 40, 30, 18};
        values1_2_multiplied[1] = new double[4] {0, -3, -12, -13};

        values1_2_summed[0] = new double[4] {15, 22, 17, 11};
        values1_2_summed[1] = new double[4] {-1, 2, 11, 12};

        values1_2_subtract[0] = new double[4] {11, 18, 13, 7};
        values1_2_subtract[1] = new double[4] {1, 4, 13, 14};

        matrix1_2_multiplied = Matrix(values1_2_multiplied, 2, 4);
        matrix1_2_summed = Matrix(values1_2_summed, 2, 4);
        matrix1_2_subtract = Matrix(values1_2_subtract, 2, 4);

        matrix1 = Matrix(values1, 2, 4);
        matrix2 = Matrix(values2, 2, 4);

        matrix3 = Matrix(values1, 2, 2); // Матрица, отличной от других размерности

        row1 = Vector(values1[0], 4, Row);
        row2 = Vector(values2[0], 4, Row);

        row3 = Vector(values1[0], 2, Row); // Строка, отличной от других размерности

        row1_2_multiplied = Vector(values1_2_multiplied[0], 4, Row);
        row1_2_summed = Vector(values1_2_summed[0], 4, Row);
        row1_2_subtract = Vector(values1_2_subtract[0], 4, Row);

        col1 = Vector(values1[1], 4, Column);
        col2 = Vector(values2[1], 4, Column);

        col3 = Vector(values1[0], 2, Column); // Столбец, отличной от других размерности

        col1_2_multiplied = Vector(values1_2_multiplied[1], 4, Column);
        col1_2_summed = Vector(values1_2_summed[1], 4, Column);
        col1_2_subtract = Vector(values1_2_subtract[1], 4, Column);


    }

    void TearDown() override {
        delete[] values1[0];
        delete[] values1[1];

        delete[] values2[0];
        delete[] values2[1];

        delete[] values1_2_subtract[0];
        delete[] values1_2_subtract[1];

        delete[] values1_2_summed[0];
        delete[] values1_2_summed[1];

        delete[] values1_2_multiplied[0];
        delete[] values1_2_multiplied[1];

        delete[] values1;
        delete[] values2;
        delete[] values1_2_multiplied;
        delete[] values1_2_summed;
        delete[] values1_2_subtract;
    }
};

TEST_F(ThirdPointTest, MatrixMultiplyTest) {

    matrix1 *= matrix2; // Поэлементное умножение через оператор *=
    EXPECT_EQ(matrix1, matrix1_2_multiplied);

    EXPECT_THROW(matrix1 *= matrix3, std::runtime_error); // Умножение матриц разной размерности - ошибка

}

TEST_F(ThirdPointTest, MatrixSumTest) {

    EXPECT_EQ(matrix1 + matrix2, matrix1_2_summed);

    EXPECT_THROW(matrix1 += matrix3, std::runtime_error); // Сложение матриц разной размерности - ошибка

}

TEST_F(ThirdPointTest, MatrixSubtractTest) {

    EXPECT_EQ(matrix1 - matrix2, matrix1_2_subtract);

    EXPECT_THROW(matrix1 -= matrix3, std::runtime_error); // Вычитание матриц разной размерности - ошибка

}

TEST_F(ThirdPointTest, VectorMathOperationTest) {

    EXPECT_EQ(row1 + row2, row1_2_summed);
    EXPECT_EQ(row1 - row2, row1_2_subtract);
    row1 *= row2;
    EXPECT_EQ(row1, row1_2_multiplied);

    EXPECT_EQ(col1 + col2, col1_2_summed);
    EXPECT_EQ(col1 - col2, col1_2_subtract);
    col1 *= col2;
    EXPECT_EQ(col1, col1_2_multiplied);

    EXPECT_THROW(col1 *= col3, std::runtime_error);
    EXPECT_THROW(col1 += col3, std::runtime_error);
    EXPECT_THROW(col1 -= col3, std::runtime_error);
}
