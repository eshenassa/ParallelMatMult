#include "Matrix.h"
#include <iostream>
#include <random>
// randomly generates an NxN matrix, M
// calculates M*M with N/4 threads

// For future:
// - allow user to specify multiple sizes
// - include sparse matrices
// - allow user to specify thread count
// - allow n-dimensional array multiplication
// - parallelize transpose and creation as well

int main(int argc, char* argv[]) {
    if (argc < 5 || argc > 6) {
        std::cout<<"Usage: ./runner <ROWS1> <COLS1> <ROWS2> <COLS2>"<<std::endl;
        exit(1);
    }
    int r1 = std::atoi(argv[1]);
    int c1 = std::atoi(argv[2]);
    int r2 = std::atoi(argv[3]);
    int c2 = std::atoi(argv[4]);
    Matrix m1(r1, c1);
    Matrix m2(r2, c2);

    std::cout<<"Matrix 1:"<<std::endl;
    m1.print();
    std::cout<<"Matrix 2:"<<std::endl;
    m2.print();

    // std::cout<<"Transposing matrices"<<std::endl;
    // m1.transpose();
    // m2.transpose();
    // std::cout<<"Matrix 1:"<<std::endl;
    // m1.print();
    // std::cout<<"Matrix 2:"<<std::endl;
    // m2.gettranspose().print();

    std::cout<<"multiplying matrices"<<std::endl;
    Matrix P = m1 * m2;
    P.print();

    return 0;
}

