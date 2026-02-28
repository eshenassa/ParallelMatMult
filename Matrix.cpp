#include "Matrix.h"
#include <thread>
#include <iostream> 
#include <random>   // for initializing matrix in fill()
#include <format>   // for formatting ostream in print()
#include <vector>   // for storing threads in matmul()
#include <functional> // Required for std::ref and std::cref; passing non-copy arguments to thread in slicemult()

Matrix::Matrix(int r, int c, bool filled) {
    this->nrow = r;
    this->ncol = c;
    this->mat = new double*[r];

    for (int i = 0; i < r; i++) 
        this->mat[i] = new double[c];
    if (filled) this->fill();
}

Matrix::~Matrix() {
    for (int i = 0; i < this->nrow; i++) 
        delete[] this->mat[i];
    delete[] this->mat;
}

Matrix Matrix::gettranspose() const{
    Matrix T = Matrix(this->ncol, this->nrow, false);
    for (int r = 0; r < this->nrow; r++) {
        for (int c = 0; c < this->ncol; c++)
            T[c][r] = this->mat[r][c];
    }
    return T;
}

void Matrix::transpose() {
    double **T = new double*[ncol];

    for (int r = 0; r < this->ncol; r++) {
        T[r] = new double[nrow];
        for (int c = 0; c < this->nrow; c++)
            T[r][c] = this->mat[c][r];
    }
    for (int i = 0; i < this->nrow; i++) 
        delete[] this->mat[i];
    delete[] this->mat;

    this->mat = T;
    int temp = ncol;
    ncol = nrow;
    nrow = temp;
}

double*& Matrix::operator[](int x) {
    return this->mat[x];
}

void Matrix::fill() {
    std::random_device rd;
    std::mt19937 gen;
    gen.seed(rd());
    // gen.seed(1);
    std::uniform_real_distribution<> dist(-1000, 1000);
    for (int i = 0; i < this->nrow; i++) {
        for (int j = 0; j < this->ncol; j++)
            this->mat[i][j] = dist(gen);
    }
}

void Matrix::print() const{
    for (int r = 0; r < this->nrow; r++) {
        for (int c = 0; c < this->ncol; c++) {
            std::cout<<std::format("{:.2f}", this->mat[r][c])<<"\t";
        }
        std::cout<<"\n";
    }
    std::cout<<std::endl;
}

int Matrix::getcols() const { return this->ncol;}
int Matrix::getrows() const { return this->nrow;}
double Matrix::get(int r, int c) const {return this->mat[r][c];}    // safe read-only element access
const double* Matrix::getrow(int r) const { // used in 
    return mat[r];
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {  // single threaded multiplication
    return matmult(m1, m2, 1);
    // if (m1.getcols() != m2.getrows()) {
    //     std::cout<<"ERROR: mult size mismatch; returning m1"<<std::endl;
    //     return m1;
    // }
    // int nrows = m1.getrows(), ncols = m2.getcols(), dim3 = m2.getrows();
    // Matrix T = m2.gettranspose();
    // Matrix product(nrows, ncols, false);
    // for (int r = 0; r < nrows; r++) {
    //     for (int c = 0; c < ncols; c++) {
    //         product[r][c] = 0;
    //         for (int v = 0; v < dim3; v++) {
    //             product[r][c] += m1.get(r, v) * T.get(c, v);
    //         }
    //     }
    // }
    // return product;
}

Matrix matmult(const Matrix& m1, const Matrix& m2, int nthreads) {  // parallelized multiplication
    if (m1.getcols() != m2.getrows()) {
        std::cout<<"ERROR: mult size mismatch; returning m1"<<std::endl;
        return m1;
    }
    if (m1.getrows() < nthreads) {
        std::cout<<"ERROR: more threads than rows; returning m1"<<std::endl;
        return m1;
    }
    int nrows = m1.getrows(), ncols = m2.getcols();
    Matrix T = m2.gettranspose();
    Matrix product(nrows, ncols, false);

    std::vector<std::thread> threads;
    for (int i = 0; i < nthreads; i++) {
        int r0 = i*nrows/nthreads, r1 = std::min(nrows, (i+1)*nrows/nthreads);
        // threads.emplace_back([&, r0, r1](){slicemult(m1, T, product, r0, r1);});
        threads.emplace_back(slicemult, std::cref(m1), std::ref(T), std::ref(product), r0, r1);
        // apparently threads can't accept non-copiable params, so need to use cref and ref
    }
    for (int i = 0; i < nthreads; i++) {
        threads[i].join();
    }
    return product;
}

// deprecated
double* vectmult(const Matrix& a, const double* b) {
    int rows = a.getrows(), cols = a.getcols();
    double* product = new double[rows];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            product[r] += a.get(r, c) * b[c];
        }
    }
    return product;
}


/*
* Usage: for use in a single thread
*
* @param a, b: operands of the multiplication; b is already transposed
* @param product: reference to result matrix 
* @param startrow, endrow: starting and ending rows of matrix a to multiply
*/
void slicemult(const Matrix& a, const Matrix& b, Matrix& product, int startrow, int endrow) {
    int ncols = b.getcols(), dim3 = b.getrows();
    for (int r = startrow; r < endrow; r++) {
        for (int c = 0; c < ncols; c++) {
            product[r][c] = 0;
            for (int v = 0; v < dim3; v++) {
                product[r][c] += a.get(r, v) * b.get(c, v);
            }
        }
    }
}

