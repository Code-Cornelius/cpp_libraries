#include <iostream>
#include "timer.h"


extern "C" {
void dgemm_(const char &TRANSA, const char &TRANSB,
            const int &M, const int &N, const int &K,
            const double &ALPHA, const double *A, const int &LDA,
            const double *B, const int &LDB,
            const double &BETA, double *C, const int &LDC);
void dgemv_(const char &TRANS, const int &M, const int &N,
            const double &ALPHA, const double *A, const int &LDA,
            const double *X, const int &INCX,
            const double &BETA, double *Y, const int &INCY);
double ddot_(const int &N, const double *X, int &INCX, double *Y,
             int &INCY);
}

void print_matrix(const int N, const double *A) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << A[i * N + j] << " ";
        }
        std::cout << '\n';
    }
}

extern "C"
double ddot_(const int &N, const double *X, int &INCX, double *Y, int &INCY);

int main() {
    // vectors
    int N = 1000;
    double *a = new double[N];
    double *b = new double[N];

    // initialize vectors with random numbers
    srand48(42);
    for (int i = 0; i < N; ++i) {
        a[i] = drand48();
        b[i] = drand48();
    }

    // compute scalar product
    int inc = 1;
    double d = ddot_(N, &a[0], inc, &b[0], inc);
    std::cout << "a . b = " << d << std::endl;

    // deallocate
    delete[] a;
    delete[] b;

    // declare some variables
    bool print = false;
    Timer timer;
    int incx, incy;
    double alpha, beta;
    double speed;

    // matrices
    double *A = new double[N * N];
    double *B = new double[N * N];
    double *C = new double[N * N];

    // initialize matrices (note: we choose column major order!)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i + j * N] = 1.;
            B[i + j * N] = 2.;
            C[i + j * N] = 3.;
        }
    }

    // blas level 1
    incx = 1;
    incy = 1;
    timer.start();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i + j * N] = ddot_(N, &A[i], incx, &B[j * N], incy);
        }
    }
    timer.stop();
    speed = 2. * N * N * N / timer.duration() * 1.e-9;
    std::cout << "BLAS LEVEL 1: ddot ---\n";
    std::cout << "SPEED GFLOPs/sec: " << speed << '\n';
    if (print) print_matrix(N, C);

    // blas level 2
    incx = 1;
    incy = 1;
    alpha = 1.;
    beta = 0.;
    timer.start();
    for (int j = 0; j < N; ++j) {
        dgemv_('N', N, N, alpha, &A[0], N, &B[j * N], incx, beta, &C[j * N], incy);
    }
    timer.stop();
    speed = 2. * N * N * N / timer.duration() * 1.e-9;
    std::cout << "BLAS LEVEL 2: dgemv ---\n";
    std::cout << "SPEED GFLOPs/sec: " << speed << '\n';
    if (print) print_matrix(N, C);

    // blas level 3
    alpha = 1.;
    beta = 0.;
    timer.start();
    dgemm_('N', 'N', N, N, N, alpha, &A[0], N, &B[0], N, beta, &C[0], N);
    timer.stop();
    speed = 2. * N * N * N / timer.duration() * 1.e-9;
    std::cout << "BLAS LEVEL 3: dgemm ---\n";
    std::cout << "SPEED GFLOPs/sec: " << speed << '\n';
    if (print) print_matrix(N, C);

    // deallocate matrices
    delete[] A;
    delete[] B;
    delete[] C;
    std::cout << " It works !!! ";

}