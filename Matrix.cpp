#include "Matrix.h"
#include <semaphore>
#include <thread>
#include <iostream>
#include <random>
#include <format>

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
double Matrix::get(int r, int c) const {return this->mat[r][c];}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.getcols() != m2.getrows()) {
        std::cout<<"ERROR: mult size mismatch; returning m1"<<std::endl;
        return m1;
    }
    int nrows = m1.getrows(), ncols = m2.getcols(), dim3 = m2.getrows();
    Matrix T = m2.gettranspose();
    Matrix product(nrows, ncols, false);
    for (int r = 0; r < nrows; r++) {
        for (int c = 0; c < ncols; c++) {
            product[r][c] = 0;
            for (int v = 0; v < dim3; v++) {
                product[r][c] += m1.get(r, v) * T.get(c, v);
            }
        }
    }
    return product;
}
