//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>
#include "matrix.h"

class CadModel
{
public:
    CadModel(const QString& file_name);
    ~CadModel();
    int triangles() const;
    Matrix get_triangle(int i) const;

protected:

private:
    const int MAX_POINTS = 10000;
    const int MAX_COORDS = 10000;
    int m_points;
    int m_coords;
    float* m_x;
    float* m_y;
    float* m_z;
    int* m_a;
    int* m_b;
    int* m_c;

    void parse_file(FILE* ffi);
    void parse_point_line(char* buf);
    void parse_coord_line(char* buf);
    void add_point(float x, float y, float z);
    void add_coord(int a, int b, int c);
};

#endif // _CAD_MODEL_H_
