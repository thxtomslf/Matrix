#include <iostream>
#include "../include/Matrix.h"
#include "../include/Vector.h"


int main() {
    double **values = new double*[3];

    values[0] = new double[3]{1, 2, 3};
    values[1] = new double[3]{3, 2, 1};
    values[2] = new double[3]{1, 1, 1};


    Matrix matrix(values, 3, 3);
    std::cout << matrix;
    std::cout << "\n";
    std::cout << matrix.getDiagonal(true);
    std::cout << "\n";
    std::cout << "\n";
    std::cout << matrix.getTransposed();
    std::cout << "\n";
    matrix *= 10;
    std::cout << matrix;
    std::cout << "\n";
    std::cout << (matrix * matrix);

    for (size_t i = 0; i < 3; ++i) {
        delete[] values[i];
    }

    delete[] values;
}
