#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "matrix3x3.h"

#define PI 3.1415926536

Matrix3x3::Matrix3x3()
{
    clear();
}

Matrix3x3::~Matrix3x3()
{
}

void Matrix3x3::clear(void)
{
    int n = MATRIX_ROWS * MATRIX_COLS;
    for (int i = 0; i < n; i++)
        m_v[i] = 0.0;
}

void Matrix3x3::unity(float scale)
{
    clear();
    for (int r = 0; r < MATRIX_ROWS; r++) {
        m_v[r * MATRIX_COLS + r] = scale;
    }
}

const float* Matrix3x3::data() const
{
    return (float*) &m_v;
}

Matrix3x3 Matrix3x3::transpose(void) const
{
    Matrix3x3 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[c * MATRIX_COLS + r] = m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

void Matrix3x3::copy(const Matrix3x3 &m)
{
    for (int i = 0; i < (MATRIX_ROWS * MATRIX_COLS); i++) {
        m_v[i] = m.m_v[i];
    }
}

Matrix3x3 Matrix3x3::operator * (float v) const
{
    Matrix3x3 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS +  c] * v;
        }
    }
    return t;
}

Matrix3x3 Matrix3x3::operator * (const Matrix3x3 &m) const
{
    Matrix3x3 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            float acc = 0.0;
            for (int j = 0; j < MATRIX_COLS; j++) {
                acc += (m_v[r * MATRIX_COLS + j] * m.m_v[j * MATRIX_COLS + c]);
            }
            t.m_v[r * MATRIX_COLS + c] = acc;
        }
    }
    return t;
}

Matrix3x3 Matrix3x3::operator + (const Matrix3x3 &m) const
{
    Matrix3x3 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS + c] + m.m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3 &m) const
{
    Matrix3x3 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS + c] - m.m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

float Matrix3x3::get(int row, int col) const
{
    return m_v[row * MATRIX_COLS + col];
}

Float3 Matrix3x3::get_row(int row) const
{
    Float3 v;
    v.v1 = get(row, 0);
    v.v2 = get(row, 1);
    v.v3 = get(row, 2);
    return v;
}

Float3 Matrix3x3::get_col(int col) const
{
    Float3 v;
    v.v1 = get(0, col);
    v.v2 = get(1, col);
    v.v3 = get(2, col);
    return v;
}

void Matrix3x3::set(int row, int col, float v)
{
    m_v[row * MATRIX_COLS + col] = v;
}

void Matrix3x3::set_row(int row, Float3& vector)
{
    set(row, 0, vector.v1);
    set(row, 1, vector.v2);
    set(row, 2, vector.v3);
}

void Matrix3x3::set_col(int col, Float3& vector)
{
    set(0, col, vector.v1);
    set(1, col, vector.v2);
    set(2, col, vector.v3);
}

void Matrix3x3::show(const char* msg) const
{
    printf("%s\n", msg);
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            printf("    %9.6f ", m_v[r * MATRIX_COLS + c]);
        }
        printf("\n");
    }
}

void Matrix3x3::rotate_ax(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix3x3 ta;
    Matrix3x3 tb;
    ta.unity();
    ta.set(1, 1, cosa);
    ta.set(1, 2, -sina);
    ta.set(2, 1, sina);
    ta.set(2, 2, cosa);
    tb = *this * ta;
    *this = tb;
}

void Matrix3x3::rotate_ay(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix3x3 ta;
    Matrix3x3 tb;
    ta.unity();
    ta.set(0, 0, cosa);
    ta.set(0, 2, sina);
    ta.set(2, 0, -sina);
    ta.set(2, 2, cosa);
    tb = *this * ta;
    *this = tb;
}

void Matrix3x3::rotate_az(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix3x3 ta;
    Matrix3x3 tb;
    ta.unity();
    ta.set(0, 0, cosa);
    ta.set(0, 1, -sina);
    ta.set(1, 0, sina);
    ta.set(1, 1, cosa);
    tb = *this * ta;
    *this = tb;
}

