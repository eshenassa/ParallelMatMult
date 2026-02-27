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
    int getcols() const;
    double get(int r, int c) const;
    void print() const;
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix matmult(const Matrix& a, const Matrix& b);
