#if !defined(_MATRIX_H_)
#define _MATRIX_H_

class Matrix
{
public:
    Matrix(int rows = 1, int cols = 1); // Creates a cleared matrix of specified dimension
    Matrix(const Matrix& m); // Copy constructor
    ~Matrix();
    Matrix& operator=(const Matrix& m);
    void clear(void);
    void unity(double scale = 1.0);

    Matrix operator * (double v) const;
    Matrix operator * (const Matrix& m) const;
    Matrix operator + (const Matrix& m) const;
    Matrix operator - (const Matrix& m) const;

    Matrix transpose(void) const;
    Matrix inverse(void) const;

    int rows(void) const;
    int cols(void) const;
    double get(int row, int col) const;
    void set(int row, int col, double v);
    void show(const char* msg) const;



    Matrix get_row(int row) const;
    void scale_row(int row, double v);




protected:
    int m_rows;
    int m_cols;
    double* m_v;

    int find_pivot_row(int diag_ix) const;
    void swap_rows(int row_a, int row_b);
    void set_row(int row, const Matrix& m);

    void sanity_check_constructor(int rows, int cols, const char* file, int line) const;
    void sanity_check_multiply(int row, int col, const char* file, int line) const;
    void sanity_check_add(int row, int col, const char* file, int line) const;
    void sanity_check_index(int row, int col, const char* file, int line) const;
    void sanity_check_square(const char* file, int line) const;
    void sanity_check_too_small(double v, double epsilon, const char* file, int line) const;
};

#endif // _MATRIX_H_

