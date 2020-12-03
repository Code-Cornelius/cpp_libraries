#include "eigen-3.2.10/Eigen/Dense"
#include <iostream>

int main(){
    int D = 5;
    // create a matrix :

    Eigen::MatrixXd matrix_data_cov(D, D);
    for (size_t i{0}; i < D; ++i) {
        for (size_t j{0}; j < D; ++j) {
            matrix_data_cov(i, j) = 1;
        }
    }
    Eigen::EigenSolver <Eigen::MatrixXd> EIGENSOLVER(matrix_data_cov);
    std::cout << EIGENSOLVER.eigenvalues();

    return 0;
}
