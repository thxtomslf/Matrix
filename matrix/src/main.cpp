#include <iostream>
#include "../include/Matrix.h"
#include "../include/Vector.h"


int main() {
    double **values = new double*[3];

    values[0] = new double[3]{1, 2, 3};
    values[1] = new double[3]{3, 2, 1};
    values[2] = new double[3]{1, 1, 1};


    Matrix matrix(values, 3, 3);
    matrix.printMatrix();
    std::cout << "\n";
    matrix.getDiagonal(true).printVector();
    std::cout << "\n";
    std::cout << "\n";
    matrix.getTransposed().printMatrix();
    std::cout << "\n";
    matrix *= 10;
    matrix.printMatrix();
    std::cout << "\n";
    (matrix * matrix).printMatrix();
}