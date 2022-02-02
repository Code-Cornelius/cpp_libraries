#include "matrix_multiplication.hpp"

// Good implementation  IJK same as JIK 1.25 misses/iter
// row order
void mm0(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    value_t sum;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            sum = 0.0;
            for (std::size_t k = 0; k < N; ++k) {
                // 2*N + 1 misses/elmnt, but easier to optimise
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}
