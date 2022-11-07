#include "gtest/gtest.h"

#include "../include/Matrix.h"
#include "../include/Vector.h"



// 2) возможность создания матрицы из векторов или чисел, вектора из чисел
class SecondPointTests : public ::testing::Test {
protected:
    Matrix matrixFromNumbers;
    Matrix matrixFromRows;
    Matrix matrixFromColumns;
    Vector rowFromValues;
    Vector columnFromValues;

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
    EXPECT_EQ(matrixFromNumbers[0], Vector(values[0], 2, Row));
    EXPECT_EQ(matrixFromNumbers[1], Vector(values[1], 2, Row));
    EXPECT_EQ(matrixFromNumbers[2], Vector(values[2], 2, Row));

}

TEST_F(SecondPointTests, MatrixFromRowsTest) {

    Vector *rows = new Vector[3];
    for (size_t i = 0; i < 3; ++i) {
        rows[i] = Vector(values[i], 2, Row);
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

    Vector *columns = new Vector[3];
    for (size_t i = 0; i < 3; ++i) {
        columns[i] = Vector(values[i], 2, Column);
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

    rowFromValues = Vector(values[0], 2, Row);
    columnFromValues = Vector(values[2], 2, Column);

    EXPECT_EQ(rowFromValues[0], values[0][0]);
    EXPECT_EQ(rowFromValues[1], values[0][1]);

    EXPECT_EQ(columnFromValues[0], values[2][0]);
    EXPECT_EQ(columnFromValues[1], values[2][1]);

}
