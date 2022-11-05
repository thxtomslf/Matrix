#include "gtest/gtest.h"

#include "../include/Vector.h"
#include "../include/Matrix.h"


// 1) обращение по индексам к элементам, извлечение диагонали, строки или столбца - 1б
// (после модификации исходной матрицы извлечённые элементы меняться не должны)
class FirstPointTests : public ::testing::Test {
protected:
    Matrix matrix;
    double **values = new double*[4];


    Vector vector1; // Вектор элементов главной диагонали матрицы matrix1
    Vector vector2; // Вектор побочной диагонали матрицы matrix1
    double *vectorValues1 = new double[4] {1, 6, 11, 16};
    double *vectorValues2 = new double[4] {4, 7, 10, 13};
    void SetUp() override {
        values[0] = new double[4] {1, 2, 3, 4};
        values[1] = new double[4] {5, 6, 7, 8};
        values[2] = new double[4] {9, 10, 11, 12};
        values[3] = new double[4] {13, 14, 15, 16};
        matrix = Matrix(values, 4, 4);

        vector1 = Vector(vectorValues1, 4, Row);
        vector2 = Vector(vectorValues2, 4, Row);
    }

    void TearDown() override {
        for (size_t i = 0; i < 4; ++i) {
            delete[] values[i];
        }
        delete[] values;

        delete[] vectorValues1;
        delete[] vectorValues2;
    }
};

TEST_F(FirstPointTests, MatrixIndexTest) {
    EXPECT_EQ(matrix[0][3], 4);  // Проверяем получение по индексу
    EXPECT_EQ(matrix[1][2], 7);
    EXPECT_EQ(matrix[2][0], 9);
    EXPECT_EQ(matrix[3][1], 14);

    matrix[0][3] = 1000;
    matrix[1][2] = 2000;
    matrix[2][0] = 3000;
    matrix[3][1] = 4000;

    EXPECT_EQ(matrix[0][3], 1000);  // Проверяем изменение по индексу
    EXPECT_EQ(matrix[1][2], 2000);
    EXPECT_EQ(matrix[2][0], 3000);
    EXPECT_EQ(matrix[3][1], 4000);

    EXPECT_THROW(matrix[0][100], std::runtime_error); // Проверяем наличие исключения при выходе за границы матрицы
}

TEST_F(FirstPointTests, MatrixDiagonalTest) {
    EXPECT_EQ(vector1, matrix.getDiagonal(true)); // Берем главную диагональ
    EXPECT_EQ(vector2, matrix.getDiagonal(false)); // Берем побочную диагональ
}


TEST_F(FirstPointTests, RowTest) {


    Vector firstRow(values[0], 4, Row);
    Vector lastRow(values[3], 4, Row);
    EXPECT_EQ(matrix[0], firstRow); // Извлекаем строки по индексу и сравниваем
    EXPECT_EQ(matrix[3], lastRow);

    EXPECT_NE(matrix[0], lastRow);

    EXPECT_THROW(EXPECT_EQ(matrix[100], firstRow), std::runtime_error); // Проверяем наличие исключения при выходе за границы

    // Проверяем, что после модификации матрицы извлеченные строки не меняются
    Vector row = matrix[0];
    matrix[0][0] *= 100;
    EXPECT_NE(row, matrix[0]);

}

TEST_F(FirstPointTests, ColumnTest) {

    double *firstColValues = new double[4] {1, 5, 9, 13};
    double *lastColValues = new double[4] {4, 8, 12, 16};
    Vector firstCol(firstColValues, 4, Column);
    Vector lastCol(lastColValues, 4, Column);
    EXPECT_EQ(matrix.getColumn(0), firstCol);
    EXPECT_EQ(matrix.getColumn(3), lastCol);

    EXPECT_NE(matrix.getColumn(0), lastCol);

    EXPECT_THROW(EXPECT_EQ(matrix.getColumn(100), firstCol), std::runtime_error); // Проверяем наличие исключения при выходе за границы

    // Проверяем, что после модификации матрицы извлеченные столбцы не меняются
    Vector row = matrix[0];
    matrix[0][0] *= 100;
    EXPECT_NE(row, matrix[0]);

}
