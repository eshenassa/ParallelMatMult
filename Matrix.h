#pragma once

class Matrix {
    private:
    int nrow, ncol;
    double** mat;

    void fill();

    public:
    Matrix(int r, int c, bool filled = true);
    ~Matrix();
    Matrix gettranspose() const;
    void transpose();
    double*& operator[](int x);
    int getrows() const;
    const double* getrow(int r) const;   // returns entire row of matrix
    int getcols() const;
    double get(int r, int c) const;
    void print() const;
};

Matrix operator*(const Matrix& a, const Matrix& b); // single threaded
Matrix matmult(const Matrix& a, const Matrix& b, int threadcount = 6);   // parallelized
double* vectmult(const Matrix& a, const double* b); // b is a vector (1xN Matrix)
void slicemult(const Matrix& a, const Matrix& b, Matrix& product, int startrow, int endrow);
