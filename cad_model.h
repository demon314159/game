//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>

class CadModel
{
public:
    CadModel(const QString& file_name);

protected:

private:
    int m_points;
    int m_coords;

    void parse_file(FILE* ffi);
    void parse_point_line(char* buf);
    void parse_coord_line(char* buf);
    void add_point(float x, float y, float z);
    void add_coord(int a, int b, int c);
};

#endif // _CAD_MODEL_H_
