#include <iostream>
#include <vector>

extern "C" {
void dgesv_(const int *N    // The number of linear equations.
        , const int *NRHS // The number of right hand sides.
        , double *A       // On entry, the N-by-N coefficient matrix A.
        // On exit, the factors L and U from the
        // factorization.
        , const int *LDA  // The leading dimension of the array A.
        , int *IPIV       // The pivot indices that define the
        // permutation matrix P.
        , double *B       // On entry, the N-by-NRHS matrix of right hand
        // side matrix B.
        // On exit, if INFO = 0, the N-by-NRHS solution
        // matrix X.
        , const int *LDB  // The leading dimension of the array B.
        , int *INFO       // = 0:  successful exit.
);
}

void print_matrix(const int N, const double *A) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << A[i + j * N] << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    const int N = 2;
    std::vector<double> A(N * N);
    std::vector<double> b(N);
    std::vector<int> ipiv(N);
    const int nrhs = 1;
    int info;

    // initialize matrix A (note: we choose column-major order!)
    A[0 + 0 * N] = 6.; // A_{1,1}
    A[1 + 0 * N] = 4.; // A_{2,1}
    A[0 + 1 * N] = 3.; // A_{1,2}
    A[1 + 1 * N] = 3.; // A_{2,2}

    // initialize right-hand ide vector b
    b[0] = 1.;
    b[1] = 2.;

    // print A
    std::cout << "A = \n";
    print_matrix(N, &A.front());

    // solve
    dgesv_(&N, &nrhs, &A.front(), &N, &ipiv.front(), &b.front(), &N, &info);

    // print L/U
    std::cout << "LU = \n";
    print_matrix(N, &A.front());

    // print the solution
    std::cout << "b = " << b[0] << " " << b[1] << '\n';

    std::cout << " It works !!! ";

}

