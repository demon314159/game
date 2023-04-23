#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include "float3.h"

class Matrix3x3
{
public:
    Matrix3x3();
    ~Matrix3x3();
    void clear(void);
    void unity(float scale = 1.0);
    const float* data() const;

    Matrix3x3 operator * (float v) const;
    Matrix3x3 operator * (const Matrix3x3& m) const;
    Matrix3x3 operator + (const Matrix3x3& m) const;
    Matrix3x3 operator - (const Matrix3x3& m) const;

    Matrix3x3 transpose(void) const;
    void rotate_ax(float angle);
    void rotate_ay(float angle);
    void rotate_az(float angle);

    float get(int row, int col) const;
    Float3 get_row(int row) const;
    Float3 get_col(int col) const;
    void set(int row, int col, float v);
    void set_row(int row, Float3& vector);
    void set_col(int col, Float3& vector);
    void show(const char* msg) const;

protected:
    static const int MATRIX_ROWS = 3;
    static const int MATRIX_COLS = 3;
    float m_v[MATRIX_ROWS * MATRIX_COLS];

    void copy(const Matrix3x3 &m);
};

#endif // _MATRIX3X3_H_

