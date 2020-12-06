#include "matrix_multiplication.hpp"

// Trivial implementation  IJK
// row order
void mmNULL(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            for (std::size_t k = 0; k < N; ++k) {
                C[i*N  + j] += A[i*N + k ] * B[k*N + j ];
            }
        }
    }
}
