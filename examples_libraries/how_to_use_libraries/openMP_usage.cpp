#include <omp.h> //pragma OPEN MP
//#undef _OPENMP //disable OPEN MP
#include <random>
#include <cstdio>
#include <cstdlib>
#include <iostream>

constexpr int CACHE_64_SIZE_DOUBLE = 64 / sizeof(double); // 64 BYTES of double

// Integrand
inline double F(double x, double y) {
    if (x * x + y * y < 1.) { // inside unit circle
        return 4.;
    }
    return 0.;
}

double C3(std::size_t n) {

    std::size_t nthreads{static_cast<size_t>(omp_get_max_threads())};
    auto *generators = new std::default_random_engine[nthreads];
    // 8 bc a double is 8 bytes, and cache lines are 64

    std::default_random_engine h(0); // for random seeds on the array

    // uniform distribution in [0, 1]
    std::uniform_real_distribution<double> u;

    for (std::size_t i{0}; i < nthreads; ++i) {
        // random generator with seed 0
        std::default_random_engine g(h);
        generators[CACHE_64_SIZE_DOUBLE * i] = g;
    }


    double sum = 0.;
    #pragma omp parallel for reduction(+:sum)
    for (std::size_t i = 0; i < n; ++i) {
        const int tid = omp_get_thread_num();
        sum += F(u(generators[CACHE_64_SIZE_DOUBLE * tid]), u(generators[CACHE_64_SIZE_DOUBLE * tid]));
        // Vector of ,
        // that we use by calling the generator
        // which is fixed for all dim
    }

    return sum / n;
}


int main() {


    // number of samples
    std::size_t n = 10000000;
    // reference solution
    double ref = 3.14159265358979323846;
    std::cout << omp_get_max_threads() << std::endl;
    double wt0 = omp_get_wtime();
    double res = C3(n);
    double wt1 = omp_get_wtime();
    printf("res:  %.20f\nref:  %.20f\nerror: %.20e\ntime: %.20f\n", res, ref,
           res - ref, wt1 - wt0);


    return 0;
}