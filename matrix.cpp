//
// matrix.cpp
//
#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    sanity_check_constructor(rows, cols, __FILE__, __LINE__);
    rows_ = rows;
    cols_ = cols;
    clear();
}

void Matrix::clear(void)
{
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            v_[r][c] = 0.0;
        }
    }
}

void Matrix::unity(double scale)
{
    if (rows_ != cols_) {
        printf("\n<<< '%s:(%d)': Square Matrix required, found (%d, %d) >>>\n",
            __FILE__, __LINE__, rows_, cols_);
        exit(0);
    }
    clear();
    for (int r = 0; r < rows_; r++) {
            v_[r][r] = scale;
    }
}

Matrix Matrix::transpose(void) const
{
    Matrix t(cols_, rows_);
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            t.set(c,r, v_[r][c]);
        }
    }
    return t;
}

Matrix Matrix::operator * (double v) const
{
    Matrix t(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            t.set(r, c, get(r, c) * v);
        }
    }
    return t;
}

Matrix Matrix::operator * (const Matrix &m) const
{
    sanity_check_multiply(m.rows(), m.cols(), __FILE__, __LINE__);
    Matrix t(rows_, m.cols());
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < m.cols(); c++) {
            double acc = 0.0;
            for (int j = 0; j < cols_; j++) {
                acc += (v_[r][j] * m.get(j, c));
            }
            t.set(r, c, acc);
        }
    }
    return t;
}

Matrix Matrix::operator + (const Matrix &m) const
{
    sanity_check_add(m.rows(), m.cols(), __FILE__, __LINE__);
    Matrix t(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < m.cols(); c++) {
            t.set(r, c, v_[r][c] + m.get(r, c));
        }
    }
    return t;
}

Matrix Matrix::operator - (const Matrix &m) const
{
    sanity_check_add(m.rows(), m.cols(), __FILE__, __LINE__);
    if (rows_ != m.rows() || cols_ != m.cols()) {
        printf("\n<<< '%s:(%d)': Matrices are not compatible (%d, %d) * (%d, %d) >>>\n",
            __FILE__, __LINE__, rows_, cols_, m.rows(), m.cols());
        exit(0);
    }
    Matrix t(rows_, cols_);
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < m.cols(); c++) {
            t.set(r, c, v_[r][c] - m.get(r, c));
        }
    }
    return t;
}

int Matrix::rows(void) const
{
    return rows_;
}

int Matrix::cols(void) const
{
    return cols_;
}

int Matrix::max_rows(void) const
{
    return MAX_ROWS;
}

int Matrix::max_cols(void) const
{
    return MAX_COLS;
}

double Matrix::get(int row, int col) const
{
    sanity_check_index(row, col, __FILE__, __LINE__);
    return v_[row][col];
}

void Matrix::set(int row, int col, double v)
{
    sanity_check_index(row, col, __FILE__, __LINE__);
    v_[row][col] = v;
}

void Matrix::show(const char* msg) const
{
    printf("%s\n", msg);
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            printf("    %8.6lf ", v_[r][c]);
        }
        printf("\n");
    }
}

void Matrix::sanity_check_constructor(int rows, int cols, const char* file, int line) const
{
    if (rows < 1 || cols < 1) {
        printf("\n<<< '%s:(%d)': Matrix can't be constructed: (%d, %d) >>>\n",
            file, line, rows, cols);
        exit(0);
    }
    if (rows > MAX_ROWS || cols > MAX_COLS) {
        printf("\n<<< '%s:(%d)': Matrix dimension (%d, %d) exceeded: (%d, %d) >>>\n",
            file, line, MAX_ROWS, MAX_COLS, rows, cols);
        exit(0);
    }
}

void Matrix::sanity_check_multiply(int rows, int cols, const char* file, int line) const
{
    if (cols_ != rows) {
        printf("\n<<< '%s:(%d)': Matrices can't be multiplied (%d, %d) * (%d, %d) >>>\n",
            file, line, rows_, cols_, rows, cols);
        exit(0);
    }
}

void Matrix::sanity_check_add(int rows, int cols, const char* file, int line) const
{
    if (rows_ != rows || cols_ != cols) {
        printf("\n<<< '%s:(%d)': Matrices can't be added (%d, %d) * (%d, %d) >>>\n",
            file, line, rows_, cols_, rows, cols);
        exit(0);
    }
}

void Matrix::sanity_check_index(int row, int col, const char* file, int line) const
{
    if (row < 0 || col < 0) {
        printf("\n<<< '%s:(%d)': Matrix illegal index to (%d, %d) >>>\n",
            file, line, row, col);
        exit(0);
    }
    if (row >= rows_ || col >= cols_) {
        printf("\n<<< '%s:(%d)': Matrix illegal index to (%d, %d) array: (%d, %d) >>>\n",
            file, line, rows_, cols_, row, col);
        exit(0);
    }
}
