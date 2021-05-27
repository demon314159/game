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
    ~CadModel();
    int vertices() const;
    int facets() const;
    void get_vertex(int i, double& x, double& y, double &z) const;
    void get_facet(int i, int& a, int& b, int& c) const;

protected:

private:
    const int MAX_VERTICES = 10000;
    const int MAX_FACETS = 10000;
    int m_vertices;
    int m_facets;
    double* m_x;
    double* m_y;
    double* m_z;
    int* m_a;
    int* m_b;
    int* m_c;

    void parse_file(FILE* ffi);
    void parse_vertex_line(char* buf);
    void parse_facet_line(char* buf);
    void add_vertex(double x, double y, double z);
    void add_facet(int a, int b, int c);
};

#endif // _CAD_MODEL_H_
