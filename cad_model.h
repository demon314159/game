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
    void parse_file(FILE* ffi);
    void parse_point_line(char* buf);
    void parse_coord_line(char* buf);
};

#endif // _CAD_MODEL_H_
