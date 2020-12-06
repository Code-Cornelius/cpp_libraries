#pragma once

#include <cstdint>
#include <vector>
#include <omp.h>


constexpr int BLOCK_SIZE = 8; // should be optimized for column major
// also remember : With the column-major matrix, the
//optimal block size is larger since the inner loops read the matrices contiguously.


using value_t = double;
using matrix_t = std::vector<value_t>;
using function_t = void (*)(matrix_t const &, matrix_t const &, matrix_t &, std::size_t N);

void mmNULL(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm0(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm1(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm2(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm3(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm4(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm5(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm6(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm7(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm8(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm9(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

void mm10(matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept;

