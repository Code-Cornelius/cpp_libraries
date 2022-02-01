#include "matrix_multiplication.hpp"

extern "C" {
void dgemm_(const char &TRANSA, const char &TRANSB,
            const int &M, const int &N, const int &K,
            const double &ALPHA, const double *A, const int &LDA,
            const double *B, const int &LDB,
            const double &BETA, double *C, const int &LDC);
}

// BLAS implementation
void mm8(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    dgemm_('N', 'N', N, N, N, 1.0, &A[0], N, &B[0], N, 0.0, &C[0], N);
}