#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "matrix.h"

Matrix::Matrix(int rows, int cols)
{
    sanity_check_constructor(rows, cols, __FILE__, __LINE__);
    m_rows = rows;
    m_cols = cols;
    m_v = new double[m_rows * m_cols];
    clear();
}

Matrix::Matrix(const Matrix& m)
{
    m_rows = m.m_rows;
    m_cols = m.m_cols;
    m_v = new double[m_rows * m_cols];
    int n = m_rows * m_cols;
    for (int i = 0; i < n; i++)
        m_v[i] = m.m_v[i];
}

Matrix::~Matrix()
{
    delete [] m_v;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if ((m_rows * m_cols) != (m.m_rows * m.m_cols)) {
        delete [] m_v;
        m_v = new double[m.m_rows * m.m_cols];
    }
    m_rows = m.m_rows;
    m_cols = m.m_cols;
    int n = m_rows * m_cols;
    for (int i = 0; i < n; i++)
        m_v[i] = m.m_v[i];
    return *this;
}

void Matrix::clear(void)
{
    int n = m_rows * m_cols;
    for (int i = 0; i < n; i++)
        m_v[i] = 0.0;
}

void Matrix::unity(double scale)
{
    sanity_check_square(__FILE__, __LINE__);
    clear();
    for (int r = 0; r < m_rows; r++) {
        m_v[r * m_cols + r] = scale;
    }
}

void Matrix::swap_rows(int row_a, int row_b)
{
    if (row_a != row_b) {
        for (int c = 0; c < m_cols; c++) {
            double temp = m_v[row_a * m_cols + c];
            m_v[row_a * m_cols + c] = m_v[row_b * m_cols + c];
            m_v[row_b * m_cols + c] = temp;
        }
    }
}

void Matrix::scale_row(int row, double v)
{
    for (int c = 0; c < m_cols; c++)
        m_v[row * m_cols + c] *= v;
}

Matrix Matrix::transpose(void) const
{
    Matrix t(m_cols, m_rows);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            t.m_v[c * m_cols + r] = m_v[r * m_cols + c];
        }
    }
    return t;
}

Matrix Matrix::operator * (double v) const
{
    Matrix t(m_rows, m_cols);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            t.m_v[r * m_cols + c] = m_v[r * m_cols +  c] * v;
        }
    }
    return t;
}

Matrix Matrix::operator * (const Matrix &m) const
{
    sanity_check_multiply(m.rows(), m.cols(), __FILE__, __LINE__);
    Matrix t(m_rows, m.m_cols);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m.m_cols; c++) {
            double acc = 0.0;
            for (int j = 0; j < m_cols; j++) {
                acc += (m_v[r * m_cols + j] * m.m_v[j * m.m_cols + c]);
            }
            t.m_v[r * t.m_cols + c] = acc;
        }
    }
    return t;
}

Matrix Matrix::operator + (const Matrix &m) const
{
    sanity_check_add(m.rows(), m.cols(), __FILE__, __LINE__);
    Matrix t(m_rows, m_cols);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            t.m_v[r * m_cols + c] = m_v[r * m_cols + c] + m.m_v[r * m_cols + c];
        }
    }
    return t;
}

Matrix Matrix::operator - (const Matrix &m) const
{
    sanity_check_add(m.rows(), m.cols(), __FILE__, __LINE__);
    Matrix t(m_rows, m_cols);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            t.m_v[r * m_cols + c] = m_v[r * m_cols + c] - m.m_v[r * m_cols + c];
        }
    }
    return t;
}

Matrix Matrix::inverse(void) const
{
    sanity_check_square(__FILE__, __LINE__);
    Matrix a = *this;
    Matrix b = *this;
    b.unity(1.0);

    for (int diag_ix = 0; diag_ix < m_cols; diag_ix++) {
        int pivot_row_ix = a.find_pivot_row(diag_ix);
        a.swap_rows(diag_ix, pivot_row_ix);
        b.swap_rows(diag_ix, pivot_row_ix);
        //
        // Check that pivot row element is not too small
        //
        double mf = a.m_v[diag_ix * m_cols + diag_ix];
        sanity_check_too_small(fabs(mf), 1.0e-9, __FILE__, __LINE__);
        //
        // Divide elements in row by pivot element
        //
        a.scale_row(diag_ix, 1.0 / mf);
        b.scale_row(diag_ix, 1.0 / mf);
        //
        // Zero column of pivot element
        //
        for (int row_ix = 0 ; row_ix < m_rows; row_ix++) {
            if (row_ix != diag_ix) {
                mf = a.m_v[row_ix * m_cols + diag_ix];
                a.set_row(row_ix, a.get_row(row_ix) - a.get_row(diag_ix) * mf);
                b.set_row(row_ix, b.get_row(row_ix) - b.get_row(diag_ix) * mf);
            }
        }
    }
    return b;
}

int Matrix::find_pivot_row(int diag_ix) const
{
    int max_ix = diag_ix;
    for (int row_ix = diag_ix + 1; row_ix < m_rows; row_ix++) {
        if (fabs(m_v[row_ix * m_cols + diag_ix]) > fabs(m_v[max_ix * m_cols + diag_ix])) {
            max_ix = row_ix;
        }
    }
    return max_ix;
}

int Matrix::rows(void) const
{
    return m_rows;
}

int Matrix::cols(void) const
{
    return m_cols;
}

double Matrix::get(int row, int col) const
{
    sanity_check_index(row, col, __FILE__, __LINE__);
    return m_v[row * m_cols + col];
}

Matrix Matrix::get_row(int row) const
{
    Matrix t(1, m_cols);
    for (int c = 0; c < m_cols; c++) {
        t.m_v[c] = m_v[row * m_cols + c];
    }
    return t;
}

void Matrix::set(int row, int col, double v)
{
    sanity_check_index(row, col, __FILE__, __LINE__);
    m_v[row * m_cols + col] = v;
}

void Matrix::set_row(int row, const Matrix& m)
{
    for (int c = 0; c < m_cols; c++) {
        m_v[row * m_cols + c] = m.m_v[c];
    }
}

void Matrix::show(const char* msg) const
{
    printf("%s\n", msg);
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            printf("    %9.6lf ", m_v[r * m_cols + c]);
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
}

void Matrix::sanity_check_multiply(int rows, int cols, const char* file, int line) const
{
    if (m_cols != rows) {
        printf("\n<<< '%s:(%d)': Matrices can't be multiplied (%d, %d) * (%d, %d) >>>\n",
            file, line, m_rows, m_cols, rows, cols);
        exit(0);
    }
}

void Matrix::sanity_check_add(int rows, int cols, const char* file, int line) const
{
    if (m_rows != rows || m_cols != cols) {
        printf("\n<<< '%s:(%d)': Matrices can't be added or subtracted (%d, %d) + (%d, %d) >>>\n",
            file, line, m_rows, m_cols, rows, cols);
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
    if (row >= m_rows || col >= m_cols) {
        printf("\n<<< '%s:(%d)': Matrix illegal index to (%d, %d) array: (%d, %d) >>>\n",
            file, line, m_rows, m_cols, row, col);
        exit(0);
    }
}

void Matrix::sanity_check_square(const char* file, int line) const
{
    if (m_cols != m_rows) {
        printf("\n<<< '%s:(%d)': Matrix must be square (%d, %d) >>>\n",
            file, line, m_rows, m_cols);
        exit(0);
    }
}

void Matrix::sanity_check_too_small(double v, double epsilon, const char* file, int line) const
{
    if (v < epsilon) {
        printf("\n<<< '%s:(%d)': Matrix value too small (%lf < %lf) >>>\n",
            file, line, v, epsilon);
        exit(0);
    }
}

