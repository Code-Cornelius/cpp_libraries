#include "matrix_multiplication.hpp"

// BLOCK SIZE WILL BE A MULTIPLE OF 2. MAKE SURE IT IS CORRECT, SO YOU GO THROUGH THE WHOLE MATRIX.
// super access version with everything optimised !
void mm6(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    matrix_t sub_matrix(BLOCK_SIZE * BLOCK_SIZE);
    value_t A_ik;

    for (std::size_t i{0}; i < N; i += BLOCK_SIZE) {
        for (std::size_t j{0}; j < N; j += BLOCK_SIZE) {

            // initialise
            for (std::size_t block_i{0}; block_i < BLOCK_SIZE; ++block_i) {
                for (std::size_t block_j{0}; block_j < BLOCK_SIZE; ++block_j) {
                    sub_matrix[block_i * BLOCK_SIZE + block_j] = 0.0;
                }
            }
            // inner product
            for (std::size_t k{0}; k < N; ++k) {
                for (std::size_t i_block{0}; i_block < BLOCK_SIZE; ++i_block) {
                    A_ik = A[(i + i_block) * N + k];
                    for (std::size_t j_block{0}; j_block < BLOCK_SIZE; ++j_block)
                        sub_matrix[i_block * BLOCK_SIZE + j_block] += A_ik * B[k * N + j + j_block];
                }
            }
            // store value
            for (size_t i_block{0}; i_block < BLOCK_SIZE; ++i_block) {
                for (size_t j_block{0}; j_block < BLOCK_SIZE; ++j_block) {
                    C[(i + i_block) * N + j + j_block] = sub_matrix[i_block * BLOCK_SIZE + j_block];
                }
            }
        }// end j

    } // end i

}
