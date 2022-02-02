#include "matrix_multiplication.hpp"

// Good implementation  JKI or KJI
void mm1(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    value_t B_jk;
    for (std::size_t j = 0; j < N; ++j) {
        for (std::size_t k = 0; k < N; ++k) {
            B_jk = B[k * N + j];
            for (std::size_t i = 0; i < N; ++i) {
                // terrible jumps for C and A. B above jump as well!
                C[i * N + j] += A[i * N + k] * B_jk;
            }
        }
    }
}
