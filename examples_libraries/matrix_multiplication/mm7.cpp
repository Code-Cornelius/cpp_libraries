#include "matrix_multiplication.hpp"

// Parallelized version 2 implementation
void mm7(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
# pragma omp parallel for  simd collapse(4) // can't do more than 3 bc loops are not perfectly nested.
    for (int i = 0; i < N; i += BLOCK_SIZE)
        for (int j = 0; j < N; j += BLOCK_SIZE)
            for (int k = 0; k < N; ++k)
                for (int tv = 0; tv < BLOCK_SIZE; ++tv) {
                    const value_t Aik = A[(i + tv) * N + k];
                    for (int th = 0; th < BLOCK_SIZE; ++th)
                        C[(i + tv) * N + j + th] += Aik * B[k * N + j + th]; // Optimized memory access for matrix B
                }
}