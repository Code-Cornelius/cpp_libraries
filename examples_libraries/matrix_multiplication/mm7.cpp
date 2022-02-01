#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include "matrix_multiplication.hpp"

// BLOCK SIZE WILL BE A MULTIPLE OF 2. MAKE SURE IT IS CORRECT, SO YOU GO THROUGH THE WHOLE MATRIX.
// Parallelized version 2 implementation. it is mm4.
void mm7(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
# pragma omp parallel for  simd collapse(4)
    for (int i = 0; i < N; i += BLOCK_SIZE)
        for (int j = 0; j < N; j += BLOCK_SIZE)
            for (int k = 0; k < N; ++k)
                for (int tv = 0; tv < BLOCK_SIZE; ++tv) {
                    const value_t Aik = A[(i + tv) * N + k];
                    for (int th = 0; th < BLOCK_SIZE; ++th)
                        C[(i + tv) * N + j + th] += Aik * B[k * N + j + th]; // Optimized memory access for matrix B
                }
}
