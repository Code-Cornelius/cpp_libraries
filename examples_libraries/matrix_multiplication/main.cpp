#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>
#include <vector>


#include "matrix_multiplication.hpp"

double benchmark(function_t f, matrix_t const &A, matrix_t const &B, matrix_t &C, std::size_t N) noexcept {
    for (std::size_t i = 0; i < N * N; ++i) {
        C[i] = 0;
    }

    auto start = std::chrono::high_resolution_clock::now();
    f(A, B, C, N);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double>(end - start).count();
}


// print the matrix.
void debug_print(std::vector<double> const &A) {
    for (std::size_t i = 0; i < sqrt(A.size()); i++) {
        std::cout << '[';
        for (std::size_t j{0}; j < sqrt(A.size()); ++j) {
            std::cout << A[i * sqrt(A.size()) + j] << ' ';
        }
        std::cout << ']' << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    // Vector of functions to benchmark
    std::vector<function_t> mm_types({mmNULL, mm0, mm1, mm2,
                                      mm3, mm4,
                                      mm5, mm6,
                                      mm7, mm8, mm9, mm10});
    std::vector<std::string> mm_types_names({"Trivial", "Trivial but ok", "Trivial reorder", "Trivial reordered second",
                                             "Direct Block Column Major", "Optimised but C bad.",
                                             "Other order of Optimised with C bad", "Improved Optimized Version",
                                             "Parallelized best version", "ISPC", "Intrinsecs", "BLAS"});

    // msudwoj: by convention, ALL_CAPS are used for preprocessor macros only
    int const RUNS = 10;
    std::vector<int> MATRIX_SIZES({128, 256, 512, 1024, 2048});
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis(0, 1);

    // Matrix to store the time and the GFLOPs/sec
    std::vector<matrix_t> times(mm_types.size(), matrix_t(MATRIX_SIZES.size()));
    std::vector<matrix_t> gflops(mm_types.size(), matrix_t(MATRIX_SIZES.size()));

    for (std::size_t i = 0; i < mm_types.size(); ++i) {
        double time = 0;
        std::cout << std::endl << mm_types_names[i] << '\n';
        for (std::size_t j = 0; j < MATRIX_SIZES.size(); ++j) {

            // creating the matrices for matrix multiplication
            matrix_t A(MATRIX_SIZES[j] * MATRIX_SIZES[j]);
            matrix_t B(MATRIX_SIZES[j] * MATRIX_SIZES[j]);
            matrix_t C(MATRIX_SIZES[j] * MATRIX_SIZES[j]);
            for (std::size_t i = 0; i < MATRIX_SIZES[j] * MATRIX_SIZES[j]; ++i) {
                A[i] = dis(gen);
                B[i] = dis(gen);
            }

            for (std::size_t k = 0; k < RUNS; ++k) {
                time += benchmark(mm_types[i], A, B, C, MATRIX_SIZES[j]);
                // the results between different mm_i functions are different because they assume different storage for the matrices.
            }

            times[i][j] = time / RUNS;
//            std::cout << MATRIX_SIZES[j] << ',' << time << '\n';

            double speed =
                    2. * MATRIX_SIZES[j] * MATRIX_SIZES[j] * MATRIX_SIZES[j] / times[i][j] * 1.e-9;
            gflops[i][j] = speed;
            std::cout << MATRIX_SIZES[j] << ", " << "SPEED GFLOPs/sec: " << speed << '\n';

        }
    }

    // Write to file
    // msudwoj: prefer ofstream im C++
    // msudwoj: see https://en.cppreference.com/w/cpp/io/basic_ofstream
    FILE *fp = nullptr;
    fp = fopen("benchmark_matrix.txt", "w");
    for (auto a_size:MATRIX_SIZES) {
        fprintf(fp, "%i ", a_size);
    }
    fprintf(fp, "\n");

    for (std::size_t i = 0; i < mm_types.size(); ++i) {
        fprintf(fp, "%s\n", mm_types_names[i].c_str());
        for (std::size_t j = 0; j < MATRIX_SIZES.size(); ++j) {
            fprintf(fp, "%lf ", times[i][j]);
        }
        fprintf(fp, "\n");
        for (std::size_t j = 0; j < MATRIX_SIZES.size();
             ++j) {
            fprintf(fp, "%lf ", gflops[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}
