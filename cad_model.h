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
    int image_size() const;
    float* image_data() const;

protected:

private:
    const int MAX_VERTICES = 10000;
    const int MAX_FACETS = 10000;
    int m_vertices;
    int m_facets;
    int m_materials;
    float* m_vertex_x;
    float* m_vertex_y;
    float* m_vertex_z;
    unsigned int* m_facet_a;
    unsigned int* m_facet_b;
    unsigned int* m_facet_c;
    float* m_image;

    void parse_file(FILE* ffi);
    void parse_vertex_line(char* buf);
    void parse_facet_line(char* buf);
    void parse_material_line(char* buf);
    void add_vertex(float x, float y, float z);
    void add_facet(unsigned int a, unsigned int b, unsigned int c);
    void add_material(unsigned int a);
    void build_image();
};

#endif // _CAD_MODEL_H_
