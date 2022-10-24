#include "gtest/gtest.h"

#include "../src/include/Matrix.h"



// 2) возможность создания матрицы из векторов или чисел, вектора из чисел
class SecondPointTests : public ::testing::Test {
protected:
    Matrix matrixFromNumbers;
    Matrix matrixFromRows;
    Matrix matrixFromColumns;
    VectorRow rowFromValues;
    VectorColumn columnFromValues;

    double **values = new double*[3];

    void SetUp() override {
        values[0] = new double[2] {1, 1};
        values[1] = new double[2] {2, 2};
        values[2] = new double[2] {3, 3};
    }

    void TearDown() override {
        delete[] values[0];
        delete[] values[1];
        delete[] values[2];
        delete[] values;
    }
};

TEST_F(SecondPointTests, MatrixFromDoubleTest) {

    matrixFromNumbers = Matrix(values, 3, 2);
    EXPECT_EQ(matrixFromNumbers[0], VectorRow(values[0], 2));
    EXPECT_EQ(matrixFromNumbers[1], VectorRow(values[1], 2));
    EXPECT_EQ(matrixFromNumbers[2], VectorRow(values[2], 2));

}

TEST_F(SecondPointTests, MatrixFromRowsTest) {

    VectorRow *rows = new VectorRow[3];
    for (size_t i = 0; i < 3; ++i) {
        rows[i] = VectorRow(values[i], 2);
    }

    matrixFromRows = Matrix(rows, 3, 2);

    EXPECT_EQ(matrixFromRows[0], rows[0]);
    EXPECT_EQ(matrixFromRows[1], rows[1]);
    EXPECT_EQ(matrixFromRows[2], rows[2]);

    // Меняем значения массива векторов
    rows[0][1] = -1000;
    rows[1][0] = 1000;
    EXPECT_NE(matrixFromRows[0], rows[0]);
    EXPECT_NE(matrixFromRows[1], rows[1]);

    delete[] rows;
}


TEST_F(SecondPointTests, MatrixFromColumnsTest) {

    VectorColumn *columns = new VectorColumn[3];
    for (size_t i = 0; i < 3; ++i) {
        columns[i] = VectorColumn(values[i], 2);
    }

    matrixFromColumns = Matrix(columns, 2, 3);

    EXPECT_EQ(matrixFromColumns.getColumn(0), columns[0]);
    EXPECT_EQ(matrixFromColumns.getColumn(1), columns[1]);
    EXPECT_EQ(matrixFromColumns.getColumn(2), columns[2]);

    // Меняем значения массива векторов
    columns[0][1] = -1000;
    columns[1][0] = 1000;
    EXPECT_NE(matrixFromColumns.getColumn(0), columns[0]);
    EXPECT_NE(matrixFromColumns.getColumn(1), columns[1]);

    delete[] columns;
}

TEST_F(SecondPointTests, RowAndColumnFromDouble) {

    rowFromValues = VectorRow(values[0], 2);
    columnFromValues = VectorColumn(values[2], 2);

    EXPECT_EQ(rowFromValues[0], values[0][0]);
    EXPECT_EQ(rowFromValues[1], values[0][1]);

    EXPECT_EQ(columnFromValues[0], values[2][0]);
    EXPECT_EQ(columnFromValues[1], values[2][1]);

}