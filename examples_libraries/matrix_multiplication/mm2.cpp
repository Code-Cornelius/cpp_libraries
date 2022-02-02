#include "matrix_multiplication.hpp"

// Good implementation  IKJ or KIJ 0.5 misses/iter
void mm2(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    value_t A_ik;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t k = 0; k < N; ++k) {
            A_ik = A[i*N + k];
            for (std::size_t j = 0; j < N; ++j) {
                // excellent, C and B are continuously, A reused!
                C[i * N + j] += A_ik * B[k * N + j];
            }
        }
    }
}
