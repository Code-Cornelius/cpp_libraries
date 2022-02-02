#include "matrix_multiplication.hpp"

// BLOCK SIZE WILL BE A MULTIPLE OF 2. MAKE SURE IT IS CORRECT, SO YOU GO THROUGH THE WHOLE MATRIX.

// Better block version implementation re masterised. With buffer (compared to 4, the buffer is one level higher).
void mm5(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    value_t Aik;
    for (int i = 0; i < N; i += BLOCK_SIZE)
        for (int block_i = 0; block_i < BLOCK_SIZE; ++block_i)
            for (int k = 0; k < N; ++k){ // k is not blocked, because if both loops were sticken together, you could make one single loop!
                Aik = A[(i + block_i) * N + k];
                for (int j = 0; j < N; j += BLOCK_SIZE)
                        for (int block_j = 0; block_j < BLOCK_SIZE; ++block_j)
                            // Optimized memory access for both matrices
                            C[(i + block_i) * N + j + block_j] += Aik * B[k * N + j + block_j];
}
}