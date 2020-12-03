#include <omp.h> //pragma OPEN MP
#include <iostream>
int main(){

    double sum = 0;
    size_t n = 100;
#pragma omp parallel for reduction(+:sum)
    for (std::size_t i = 0; i < n; ++i) {
        auto steve = omp_get_thread_num();
        std::cout << steve << std::endl;
        sum += 1;
    }

    std::cout << sum;

    return 0;
}