#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include "main.hpp"
#include <iomanip>
#include <cassert>

#include "matrix_multiplication.hpp"

int main() {
    // Vector of functions to benchmark
    std::vector<function_t> mm_types({mmNULL, mm0, mm1, mm2,
                                      mm3, mm4, mm5, mm6, mm7});
    std::vector<std::string> mm_types_names(
            {"Baseline: Trivial", "Trivial reordered 1", "Trivial reordered 2", "Trivial reordered 3",
             "Naive Block Column Major", "Block Column Major reordered 1",
             "Block Column Major reordered 2", "Block Column Major reordered 3",
             "OpenMP on best direct version",  "Intrinsics", "BLAS"});


    std::vector<float> c_SIZES_POWER({5, 6, 7, 8, 9, 10});
    int const c_RUNS = 1 * pow(2, c_SIZES_POWER.back() * 2);
    // will be normalised later depending on the size, so the biggest matrix get only one run.

    int c_NB_DIFF_SIZES{static_cast<int>(c_SIZES_POWER.size())};
    std::vector<long int> c_MATRIX_SIZES(c_NB_DIFF_SIZES);
    // creating sizes for matrices
    for (int i = 0; i < c_SIZES_POWER.size(); i++) {
        c_MATRIX_SIZES[i] = static_cast<long int>(pow(2, c_SIZES_POWER[i]));
    }

    std::mt19937 gen;
    std::uniform_real_distribution<double> dis(0, 1);

    // file to write results to
    std::ofstream benchmark_data;
    benchmark_data << std::setprecision(5) << std::fixed; // fix style
    std::string str_path = "C:\\Users\\nie_k\\Desktop\\travail\\comput_libraries\\my_lib_cpp\\examples_libraries\\matrix_multiplication\\";
    benchmark_data.open(str_path + "benchmark_gemm.txt", std::ios::out);

    if (!benchmark_data) { // file couldn't be opened
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }

    // writing the header: the size of matrices
    for (int matrix_size: c_MATRIX_SIZES) { // iterate over sizes
        benchmark_data << matrix_size << " ";
    }
    benchmark_data << std::endl;



    // Matrix to store the time and the GFLOPs/sec
    std::vector<matrix_t> times(mm_types.size(), matrix_t(c_NB_DIFF_SIZES));
    std::vector<matrix_t> gflops(mm_types.size(), matrix_t(c_NB_DIFF_SIZES));

    for (std::size_t i = 0; i < mm_types.size(); ++i) { // iterate over types of algorithms
        double time = 0;
        benchmark_data << mm_types_names[i] << std::endl;

        std::cout << std::endl << mm_types_names[i] << '\n';
        for (std::size_t j = 0; j < c_NB_DIFF_SIZES; ++j) { // iterate over sizes

            // creating the matrices for matrix multiplication
            int nb_param_inside_matrix = c_MATRIX_SIZES[j] * c_MATRIX_SIZES[j];
            matrix_t A(nb_param_inside_matrix);
            matrix_t B(nb_param_inside_matrix);
            matrix_t C(nb_param_inside_matrix);
            for (std::size_t i = 0; i < nb_param_inside_matrix; ++i) {
                A[i] = dis(gen); // random matrices
                B[i] = dis(gen);
            }

            int nb_runs_for_this_size{c_RUNS / nb_param_inside_matrix};
            assert(nb_runs_for_this_size != 0);
            for (std::size_t k = 0; k < nb_runs_for_this_size; ++k) {
                time += benchmark(mm_types[i], A, B, C, c_MATRIX_SIZES[j]);
                // the results between different mm_i functions are different because they assume different storage for the matrices.
                // we assume the mm algos are correct.
            }

            times[i][j] = time / nb_runs_for_this_size; // scaled time


            value_t nb_Gbits_handled =
                    2. * c_MATRIX_SIZES[j] * c_MATRIX_SIZES[j] * c_MATRIX_SIZES[j] * 1.e-9 * sizeof(value_t);
            value_t speed = nb_Gbits_handled / times[i][j];

            gflops[i][j] = speed;
            std::cout << c_MATRIX_SIZES[j] << ", " << "SPEED GFLOPs/sec: " << speed << '\n';

        }
        // writing results
        for (std::size_t j = 0; j < c_NB_DIFF_SIZES; ++j)
            benchmark_data << times[i][j] << " ";
        benchmark_data << std::endl;

        for (std::size_t j = 0; j < c_NB_DIFF_SIZES; ++j)
            benchmark_data << gflops[i][j] << " ";
        benchmark_data << std::endl;
    }

// close results file
    benchmark_data.close();


    return 0;
}
