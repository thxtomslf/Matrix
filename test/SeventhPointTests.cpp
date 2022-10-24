#include "gtest/gtest.h"
#include "../src/include/Matrix.h"


// 6) получение транспонированной и обратной матриц
class SeventhPointTests : public ::testing::Test {
protected:
    Matrix matrix;
    Matrix transposedMatrix;
    double **values = new double*[5];
    double **valuesForTransposed = new double*[5];

    void SetUp() override {
        values[0] = new double[5] {1, -2, 3, 4, 5};
        values[1] = new double[5] {6, 7, 8, -9, 0};
        values[2] = new double[5] {1, 2, 3, 4, 5};
        values[3] = new double[5] {6, 7, 8, 9, 0};
        values[4] = new double[5] {1, 2, -3, 4, 5};

        valuesForTransposed[0] = new double[5] {1, 6, 1, 6, 1};
        valuesForTransposed[1] = new double[5] {-2, 7, 2, 7, 2};
        valuesForTransposed[2] = new double[5] {3, 8, 3, 8, -3};
        valuesForTransposed[3] = new double[5] {4, -9, 4, 9, 4};
        valuesForTransposed[4] = new double[5] {5, 0, 5, 0, 5};

    }

    void TearDown() override {
        for (size_t i = 0; i < 5; ++i) {
            delete[] values[i];
            delete[] valuesForTransposed[i];
        }
        delete[] values;
        delete[] valuesForTransposed;
    }
};


TEST_F(SeventhPointTests, TransposedMatrixTest) {
    matrix = Matrix(values, 5, 5);
    transposedMatrix = Matrix(valuesForTransposed, 5, 5);

    std::cout << "Test: TransposedMatrixTest\n";
    std::cout << "Matrix:\n";
    matrix.printMatrix();
    std::cout << "Transposed Matrix:\n";
    matrix.getTransposed().printMatrix();

    EXPECT_EQ(matrix.getTransposed(), transposedMatrix);

}