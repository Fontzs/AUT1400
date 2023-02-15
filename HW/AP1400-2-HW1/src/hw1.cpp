#include "hw1.h"

#include <iomanip>
#include <random>

using std::cin;
using std::cout;
using std::endl;

namespace algebra {

Matrix CreateMatrix(size_t n, size_t m, double v) {
    Matrix x;
    for (int i = 0; i < n; i++) {
        std::vector<double> vect(m, v);
        x.push_back(vect);
    }
    return x;
}

Matrix zeros(size_t n, size_t m) { return CreateMatrix(n, m, 0); }

Matrix ones(size_t n, size_t m) { return CreateMatrix(n, m, 1); }

Matrix random(size_t n, size_t m, double min, double max) {
    Matrix x;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(min, max);

    for (int i = 0; i < n; i++) {
        std::vector<double> vect;
        for (int j = 0; j < m; j++) {
            vect.push_back(u(e));
        }
        x.push_back(vect);
    }
    return x;
}

void show(const Matrix& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << left << setw(5) << setprecision(3) << matrix[i][j];
        }
        cout << endl;
    }
}

Matrix multiply(const Matrix& matrix, double c) {
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] *= c;
        }
    }
    return matrix;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {}

Matrix sum(const Matrix& matrix, double c) {
    int m = matrix.size();
    int n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] += c;
        }
    }
    return matrix;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    int m{matrix1.size()};
    int n{matrix1[0].size()};
    Matrix x(m);
    for (int i{0}; i < m; i++) {
        std::vector<double> vect(n);
        for (int j{0}; j < n; j++) {
            vect.push_back(matrix1[i][j] + matrix2[i][j]);
        }
        x.push_back(vect);
    }

    return x;
}

}  // namespace algebra