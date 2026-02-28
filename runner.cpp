#include "Matrix.h"
#include <iostream>
#include <chrono>   // for timing
// randomly generates an NxN matrix, M
// calculates M*M with N/4 threads

// For future:
// - include sparse matrices
// - allow n-dimensional array multiplication
// - parallelize transpose and creation as well

int main(int argc, char* argv[]) {
    if (argc < 6 || argc > 7) {
        std::cout<<"Usage: ./runner <ROWS1> <COLS1> <ROWS2> <COLS2> <NTHREADS>"<<std::endl;
        exit(1);
    }
    int r1 = std::atoi(argv[1]);
    int c1 = std::atoi(argv[2]);
    int r2 = std::atoi(argv[3]);
    int c2 = std::atoi(argv[4]);
    int nthreads = std::atoi(argv[5]);
    Matrix m1(r1, c1);
    Matrix m2(r2, c2);

    // std::cout<<"Matrix 1:"<<std::endl;
    // m1.print();
    // std::cout<<"Matrix 2:"<<std::endl;
    // m2.print();

    // std::cout<<"Transposing matrices"<<std::endl;
    // m1.transpose();
    // m2.transpose();
    // std::cout<<"Matrix 1:"<<std::endl;
    // m1.print();
    // std::cout<<"Matrix 2:"<<std::endl;
    // m2.gettranspose().print();

    std::cout<<"multiplying matrices"<<std::endl;
    auto seq0 = std::chrono::high_resolution_clock::now();
    Matrix P = m1 * m2;
    auto seq1 = std::chrono::high_resolution_clock::now();

    auto seqtime = duration_cast<std::chrono::milliseconds>(seq1 - seq0).count();
    std::cout<<"sequential time:\t"<<seqtime<<"ms"<<std::endl;

    std::cout<<"multiplying matrices with threads"<<std::endl;
    auto par0 = std::chrono::high_resolution_clock::now();
    Matrix P1 = matmult(m1, m2, nthreads);
    auto par1 = std::chrono::high_resolution_clock::now();

    auto partime = duration_cast<std::chrono::milliseconds>(par1 - par0).count();
    std::cout<<"parallel time:\t\t"<<partime<<"ms"<<std::endl;

    // std::cout<< 1.0/(double)(seqtime-partime)/seqtime << "x faster"<<std::endl;
    return 0;
}

