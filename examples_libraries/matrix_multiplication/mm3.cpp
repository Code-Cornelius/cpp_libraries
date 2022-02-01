#include "matrix_multiplication.hpp"

// Block column major multiplication
void mm3(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    // the logic being, first we move on blocks (i and j).
    // Then we will move inside with iblock and jblock.
    // Finally, we add two intermediate steps with the k and kblock.
    // these steps are for the computations and follow the same rule as for i and j.

    // problem for accesses of B and probably you could get more locality upon C and A.
    for (std::size_t i = 0; i < N; i += BLOCK_SIZE) {
        for (std::size_t j = 0; j < N; j += BLOCK_SIZE) {
            for (std::size_t k = 0; k < N; k += BLOCK_SIZE) {
                for (std::size_t i_block = i; i_block < i + BLOCK_SIZE; i_block++) {
                    for (std::size_t j_block = j; j_block < j + BLOCK_SIZE; j_block++) {
                        for (std::size_t k_block = k; k_block < k + BLOCK_SIZE; k_block++) {
                            C[i_block * N + j_block] += A[i_block * N + k_block] * B[k_block * N + j_block];
                        }
                    }
                }
            }
        }
    }
}
