#include "gtest/gtest.h"

#include "../src/include/Matrix.h"


// 3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности
class ThirdPointTest : public ::testing::Test {
protected:
    Matrix matrix1;
    Matrix matrix2;
    Matrix matrix3;

    Matrix matrix1_2_multiplied;
    Matrix matrix1_2_summed;
    Matrix matrix1_2_subtract;

    VectorRow row1;
    VectorRow row2;
    VectorRow row3;

    VectorRow row1_2_multiplied;
    VectorRow row1_2_summed;
    VectorRow row1_2_subtract;

    VectorColumn col1;
    VectorColumn col2;
    VectorColumn col3;

    VectorColumn col1_2_multiplied;
    VectorColumn col1_2_summed;
    VectorColumn col1_2_subtract;

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

        row1 = VectorRow(values1[0], 4);
        row2 = VectorRow(values2[0], 4);

        row3 = VectorRow(values1[0], 2); // Строка, отличной от других размерности

        row1_2_multiplied = VectorRow(values1_2_multiplied[0], 4);
        row1_2_summed = VectorRow(values1_2_summed[0], 4);
        row1_2_subtract = VectorRow(values1_2_subtract[0], 4);

        col1 = VectorColumn(values1[1], 4);
        col2 = VectorColumn(values2[1], 4);

        col3 = VectorColumn(values1[0], 2); // Столбец, отличной от других размерности

        col1_2_multiplied = VectorColumn(values1_2_multiplied[1], 4);
        col1_2_summed = VectorColumn(values1_2_summed[1], 4);
        col1_2_subtract = VectorColumn(values1_2_subtract[1], 4);


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

    EXPECT_DEATH(matrix1 *= matrix3, ""); // Умножение матриц разной размерности - ошибка

}

TEST_F(ThirdPointTest, MatrixSumTest) {

    EXPECT_EQ(matrix1 + matrix2, matrix1_2_summed);

    EXPECT_DEATH(matrix1 += matrix3, ""); // Сложение матриц разной размерности - ошибка

}

TEST_F(ThirdPointTest, MatrixSubtractTest) {

    EXPECT_EQ(matrix1 - matrix2, matrix1_2_subtract);

    EXPECT_DEATH(matrix1 -= matrix3, ""); // Вычитание матриц разной размерности - ошибка

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

    EXPECT_DEATH(col1 *= col3, "");
    EXPECT_DEATH(col1 += col3, "");
    EXPECT_DEATH(col1 -= col3, "");
}