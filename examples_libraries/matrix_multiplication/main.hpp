//
// Created by nie_k on 01/02/2022.
//

#ifndef MY_CPP_LIBRARIES_MAIN_H
#define MY_CPP_LIBRARIES_MAIN_H

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>
#include <vector>
#include <fstream>
#include <string>

#include "matrix_multiplication.hpp"

double benchmark(function_t f, matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    for (std::size_t i = 0; i < N * N; ++i) {
        C[i] = 0;
    }

    auto start = std::chrono::high_resolution_clock::now();
    f(A, B, C, N);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double>(end - start).count();
}


// print the matrix.
void debug_print(std::vector<double> const &A) {
    for (std::size_t i = 0; i < sqrt(A.size()); i++) {
        std::cout << '[';
        for (std::size_t j{0}; j < sqrt(A.size()); ++j) {
            std::cout << A[i * sqrt(A.size()) + j] << ' ';
        }
        std::cout << ']' << std::endl;
    }
    std::cout << std::endl;
}


#endif //MY_CPP_LIBRARIES_MAIN_H
