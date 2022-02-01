#include "matrix_multiplication.hpp"

// BLOCK SIZE WILL BE A MULTIPLE OF 2. MAKE SURE IT IS CORRECT, SO YOU GO THROUGH THE WHOLE MATRIX.
// Better block version implementation, with buffer.
void mm4(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
// problem here is we access too many times to C.
// The accesses to B and A are great though !
    for (int i = 0; i < N; i += BLOCK_SIZE)
        for (int j = 0; j < N; j += BLOCK_SIZE)
            for (int k = 0; k < N; ++k)
                for (int block_i = 0; block_i < BLOCK_SIZE; ++block_i) {
                    const value_t Aik = A[(i + block_i) * N + k];
                    for (int block_j = 0; block_j < BLOCK_SIZE; ++block_j)
                        C[(i + block_i) * N + j + block_j] += Aik * B[k * N + j + block_j]; // Optimized memory access for matrix B
                }
}