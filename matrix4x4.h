#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

class Matrix4x4
{
public:
    Matrix4x4();
    ~Matrix4x4();
    void clear(void);
    void unity(float scale = 1.0);
    const float* data() const;

    Matrix4x4 operator * (float v) const;
    Matrix4x4 operator * (const Matrix4x4& m) const;
    Matrix4x4 operator + (const Matrix4x4& m) const;
    Matrix4x4 operator - (const Matrix4x4& m) const;

    Matrix4x4 transpose(void) const;
    void perspective(float fovy, float aspect, float near, float far);
    void translate(float x, float y, float z);
    void rotate_ax(float angle);
    void rotate_ay(float angle);
    void rotate_az(float angle);

    float get(int row, int col) const;
    void set(int row, int col, float v);
    void show(const char* msg) const;

protected:
    static const int MATRIX_ROWS = 4;
    static const int MATRIX_COLS = 4;
    float m_v[MATRIX_ROWS * MATRIX_COLS];

    void copy(const Matrix4x4 &m);
};

#endif // _MATRIX4X4_H_

