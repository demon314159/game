//
// matrix.h
//
#if !defined(MATRIX_H_)
#define MATRIX_H_

class Matrix
{
    static const int MAX_ROWS = 3;
    static const int MAX_COLS = 3;
public:
    Matrix(int rows = 1, int cols = 1); // Creates a cleared matrix of specified dimension
    void clear(void);
    void unity(double scale = 1.0);

    Matrix transpose(void) const;

    Matrix operator * (double v) const;
    Matrix operator * (const Matrix& m) const;
    Matrix operator + (const Matrix& m) const;
    Matrix operator - (const Matrix& m) const;

    int rows(void) const;
    int cols(void) const;
    int max_rows(void) const;
    int max_cols(void) const;
    double get(int row, int col) const;
    void set(int row, int col, double v);
    void show(const char* msg) const;
protected:
    int rows_;
    int cols_;
    double v_[MAX_ROWS][MAX_COLS];

    void sanity_check_constructor(int rows, int cols, const char* file, int line) const;
    void sanity_check_multiply(int row, int col, const char* file, int line) const;
    void sanity_check_add(int row, int col, const char* file, int line) const;
    void sanity_check_index(int row, int col, const char* file, int line) const;
};

#endif // MATRIX_H_

