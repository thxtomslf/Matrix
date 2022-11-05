#include "gtest/gtest.h"

#include "../include/Matrix.h"
#include "../include/Vector.h"


// 7) подсчёт определителя матрицы
class SixthPointTests : public ::testing::Test {
protected:
    Matrix matrix;
    double **values = new double*[5];

    Matrix wrongMatrix; // Не квадратная матрица

    void SetUp() override {
        values[0] = new double[5] {1, -2, 3, 4, 5};
        values[1] = new double[5] {6, 7, 8, -9, 0};
        values[2] = new double[5] {1, 2, 3, 4, 5};
        values[3] = new double[5] {6, 7, 8, 9, 0};
        values[4] = new double[5] {1, 2, -3, 4, 5};

        wrongMatrix = Matrix(values, 2, 5);
    }

    void TearDown() override {
        for (size_t i = 0; i < 5; ++i) {
            delete[] values[i];
        }
        delete[] values;
    }
};

TEST_F(SixthPointTests, DeterminantTest) {
    std::cout << "Test: DeterminantTest\n";
    std::cout << "Matrix:\n";
    double determinant = 0;
    matrix = Matrix(values, 2, 2);
    matrix.printMatrix();

    std::cout << "Determinant: \n";
    determinant = matrix.getDeterminant();
    std::cout << determinant;
    std::cout << "\n";

    EXPECT_NEAR(determinant, 19.0, 0.001);

    std::cout << "Matrix:\n";
    matrix = Matrix(values, 3, 3);
    matrix.printMatrix();

    std::cout << "Determinant: \n";
    determinant = matrix.getDeterminant();
    std::cout << determinant;
    std::cout << "\n";

    EXPECT_NEAR(determinant, 40.0, 0.001);

    std::cout << "Matrix:\n";
    matrix = Matrix(values, 4, 4);
    matrix.printMatrix();

    std::cout << "Determinant: \n";
    determinant = matrix.getDeterminant();
    std::cout << determinant;
    std::cout << "\n";

    EXPECT_NEAR(determinant, 720.0, 0.001);

    std::cout << "Matrix:\n";
    matrix = Matrix(values, 5, 5);
    matrix.printMatrix();

    std::cout << "Determinant: \n";
    determinant = matrix.getDeterminant();
    std::cout << determinant;
    std::cout << "\n";

    EXPECT_NEAR(determinant, 12960.0, 0.001);

    EXPECT_THROW(wrongMatrix.getDeterminant(), std::runtime_error);
}
