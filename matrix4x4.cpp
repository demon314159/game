#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "matrix4x4.h"

#define PI 3.1415926536

Matrix4x4::Matrix4x4()
{
    clear();
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::clear(void)
{
    int n = MATRIX_ROWS * MATRIX_COLS;
    for (int i = 0; i < n; i++)
        m_v[i] = 0.0;
}

void Matrix4x4::unity(float scale)
{
    clear();
    for (int r = 0; r < MATRIX_ROWS; r++) {
        m_v[r * MATRIX_COLS + r] = scale;
    }
}

const float* Matrix4x4::data() const
{
    return (float*) &m_v;
}

Matrix4x4 Matrix4x4::transpose(void) const
{
    Matrix4x4 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[c * MATRIX_COLS + r] = m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

void Matrix4x4::copy(const Matrix4x4 &m)
{
    for (int i = 0; i < (MATRIX_ROWS * MATRIX_COLS); i++) {
        m_v[i] = m.m_v[i];
    }
}

Matrix4x4 Matrix4x4::operator * (float v) const
{
    Matrix4x4 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS +  c] * v;
        }
    }
    return t;
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4 &m) const
{
    Matrix4x4 t;
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

Matrix4x4 Matrix4x4::operator + (const Matrix4x4 &m) const
{
    Matrix4x4 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS + c] + m.m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

Matrix4x4 Matrix4x4::operator - (const Matrix4x4 &m) const
{
    Matrix4x4 t;
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            t.m_v[r * MATRIX_COLS + c] = m_v[r * MATRIX_COLS + c] - m.m_v[r * MATRIX_COLS + c];
        }
    }
    return t;
}

float Matrix4x4::get(int row, int col) const
{
    return m_v[row * MATRIX_COLS + col];
}

void Matrix4x4::set(int row, int col, float v)
{
    m_v[row * MATRIX_COLS + col] = v;
}

void Matrix4x4::show(const char* msg) const
{
    printf("%s\n", msg);
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            printf("    %9.6f ", m_v[r * MATRIX_COLS + c]);
        }
        printf("\n");
    }
}

void Matrix4x4::perspective(float fovy, float aspect, float near, float far)
{
    float top = tan((fovy / 2.0) * PI / 180.0) * near;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    clear();
    set(0, 0, 2.0 * near / (right - left));
    set(0, 2, (right + left) / (right - left));
    set(1, 1, 2.0 * near / (top - bottom));
    set(1, 2, (top + bottom) / (top - bottom));
    set(2, 2, -(far + near) / (far - near));
    set(2, 3, -2.0 * far * near / (far - near));
    set(3, 2, -1.0);
    set(3, 3, 0);
}

void Matrix4x4::translate(float x, float y, float z)
{
    Matrix4x4 ta;
    Matrix4x4 tb;

    ta.unity();
    ta.set(0, 3, x);
    ta.set(1, 3, y);
    ta.set(2, 3, z);
    tb = *this * ta;
    *this = tb;
}

void Matrix4x4::rotate_ax(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix4x4 ta;
    Matrix4x4 tb;
    ta.unity();
    ta.set(1, 1, cosa);
    ta.set(1, 2, -sina);
    ta.set(2, 1, sina);
    ta.set(2, 2, cosa);
    tb = *this * ta;
    *this = tb;
}

void Matrix4x4::rotate_ay(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix4x4 ta;
    Matrix4x4 tb;
    ta.unity();
    ta.set(0, 0, cosa);
    ta.set(0, 2, sina);
    ta.set(2, 0, -sina);
    ta.set(2, 2, cosa);
    tb = *this * ta;
    *this = tb;
}

void Matrix4x4::rotate_az(float angle)
{
    float cosa = cos(angle * PI / 180.0);
    float sina = sin(angle * PI / 180.0);
    Matrix4x4 ta;
    Matrix4x4 tb;
    ta.unity();
    ta.set(0, 0, cosa);
    ta.set(0, 1, -sina);
    ta.set(1, 0, sina);
    ta.set(1, 1, cosa);
    tb = *this * ta;
    *this = tb;
}

