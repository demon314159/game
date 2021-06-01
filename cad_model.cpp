//
// cad_model.cpp
//
#include "cad_model.h"

#define PRINTY

CadModel::CadModel(const QString& file_name)
    : m_vertices(0)
    , m_facets(0)
    , m_materials(0)
    , m_vertex_x(NULL)
    , m_vertex_y(NULL)
    , m_vertex_z(NULL)
    , m_facet_a(NULL)
    , m_facet_b(NULL)
    , m_facet_c(NULL)
    , m_image(NULL)
{
    m_vertex_x = new float[MAX_VERTICES];
    m_vertex_y = new float[MAX_VERTICES];
    m_vertex_z = new float[MAX_VERTICES];
    m_facet_a = new unsigned int[MAX_FACETS];
    m_facet_b = new unsigned int[MAX_FACETS];
    m_facet_c = new unsigned int[MAX_FACETS];
    FILE* ffi = fopen(file_name.toLatin1().data(), "r");
    if (ffi == NULL) {
#ifdef PRINTY
        printf("<<< Error opening file '%s' >>>\n", file_name.toLatin1().data());
#endif
    } else {

#ifdef PRINTY
        printf("Open file '%s'\n", file_name.toLatin1().data());
#endif
        parse_file(ffi);
        fclose(ffi);
        build_image();
#ifdef PRINTY
        printf("Close file '%s'\n", file_name.toLatin1().data());
        printf("m_vertices = %d\n", m_vertices);
        printf("m_facets = %d\n", m_facets);
        printf("m_materials = %d\n", m_materials);
#endif
    }
}

CadModel::~CadModel()
{
    delete[] m_vertex_x;
    delete[] m_vertex_y;
    delete[] m_vertex_z;
    delete[] m_facet_a;
    delete[] m_facet_b;
    delete[] m_facet_c;
    if (m_image != NULL) {
        delete[] m_image;
    }
}

void CadModel::build_image()
{
    float r, g, b;
    r = 0.0;
    g = 0.0;
    b = 1.0;
    if (m_facets > 0) {
        m_image = new float[8 * 3 * m_facets];
        float* p = m_image;
        for (int i = 0; i < m_facets; i++) {
            p[0] = m_vertex_x[m_facet_a[i]];
            p[1] = m_vertex_y[m_facet_a[i]];
            p[2] = m_vertex_z[m_facet_a[i]];
            p[3] = 1.0;
            p[4] = r;
            p[5] = g;
            p[6] = b;
            p[7] = 1.0;
            p[8+0] = m_vertex_x[m_facet_b[i]];
            p[8+1] = m_vertex_y[m_facet_b[i]];
            p[8+2] = m_vertex_z[m_facet_b[i]];
            p[8+3] = 1.0;
            p[8+4] = r;
            p[8+5] = g;
            p[8+6] = b;
            p[8+7] = 1.0;
            p[16+0] = m_vertex_x[m_facet_c[i]];
            p[16+1] = m_vertex_y[m_facet_c[i]];
            p[16+2] = m_vertex_z[m_facet_c[i]];
            p[16+3] = 1.0;
            p[16+4] = r;
            p[16+5] = g;
            p[16+6] = b;
            p[16+7] = 1.0;
            p += 24;
        }
    }
}

void CadModel::parse_file(FILE* ffi)
{
    char buf[16384];
    char* ptr;
    bool vertex_flag = false;
    bool facet_flag = false;
    bool material_flag = false;

    ptr = fgets(buf, 16384, ffi);
    while (ptr != NULL) {
        if (vertex_flag) {
            if (buf[0] == ']') {
                vertex_flag = false;
            } else {
                parse_vertex_line(buf);
            }
        } else  if (facet_flag) {
            if (buf[0] == ']') {
                facet_flag = false;
            } else {
                parse_facet_line(buf);
            }
        } else  if (material_flag) {
            if (buf[0] == ']') {
                material_flag = false;
            } else {
                parse_material_line(buf);
            }

        } else {
            vertex_flag = (0 == strncmp(buf, "point [", 7)) ? true : false;
            facet_flag = (0 == strncmp(buf, "coordIndex [", 12)) ? true : false;
            material_flag = (0 == strncmp(buf, "materialIndex [", 12)) ? true : false;
        }
        ptr = fgets(buf, 16384, ffi);
    }
}

void CadModel::parse_vertex_line(char* buf)
{
    float x, y, z;
    int res, num, len;
#ifdef PRINTY
//    printf("parse_vertex_line: %s", buf);
#endif
    len = strlen(buf);
    res = sscanf(buf, "%f %f %f%n", &x, &y, &z, &num);
#ifdef PRINTY
//    printf("  len = %d, res = %d, x = %f, y = %f, z = %f, num = %d\n", len, res, x, y, z, num);
#endif
    if (res == 3) {
        add_vertex(x, y, z);
        if (buf[num] == ',' && (num < (len - 3))) {
            parse_vertex_line(buf + num + 1);
        }
    }
}

void CadModel::parse_facet_line(char* buf)
{
    unsigned int a, b, c;
    int d;
    int res, num, len;
#ifdef PRINTY
//    printf("parse_facet_line: %s", buf);
#endif
    len = strlen(buf);
    res = sscanf(buf, "%u, %u, %u, %d%n", &a, &b, &c, &d, &num);
#ifdef PRINTY
//    printf("  len = %d, res = %d, a = %u, b = %u, c = %u, d = %d, num = %d\n", len, res, a, b, c, d, num);
#endif
    if ((res == 4) && (d == -1)) {
        add_facet(a, b, c);
        if (buf[num] == ',' && (num < (len - 3))) {
            parse_facet_line(buf + num + 1);
        }
    }
}

void CadModel::parse_material_line(char* buf)
{
    int a;
    int res, num, len;
#ifdef PRINTY
//    printf("parse_material_line: %s", buf);
#endif
    len = strlen(buf);
    res = sscanf(buf, "%d%n", &a, &num);
    if (res == 1) {
        add_material(a);
        while ((res == 1) && (buf[num] == ',') && (num < (len - 3)) ) {
            buf += (num + 1);
            res = sscanf(buf, "%d%n", &a, &num);
            if (res == 1) {
                add_material(a);
            }
        }

    }
}

void CadModel::add_vertex(float x, float y, float z)
{
    if (m_vertices < MAX_VERTICES) {
        m_vertex_x[m_vertices] = x;
        m_vertex_y[m_vertices] = y;
        m_vertex_z[m_vertices] = z;
        ++m_vertices;
    }
}

void CadModel::add_facet(unsigned int a, unsigned int b, unsigned int c)
{
    if (m_facets < MAX_FACETS) {
        m_facet_a[m_facets] = a;
        m_facet_b[m_facets] = b;
        m_facet_c[m_facets] = c;
        ++m_facets;
    }
}

void CadModel::add_material(unsigned int a)
{
    ++m_materials;
}

unsigned int CadModel::vertices() const
{
    return m_vertices;
}

int CadModel::image_size() const
{
izzzzzzzzzzzzzzzzzzzzzzz    return m_facets;
}

void CadModel::get_vertex(int i, double& x, double& y, double& z) const
{
    if (i < MAX_VERTICES) {
        x = m_x[i];
        y = m_y[i];
        z = m_z[i];
    } else {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
}

void CadModel::get_facet(int i, int& a, int& b, int& c) const
{
    if (i < MAX_FACETS) {
        a = m_a[i];
        b = m_b[i];
        c = m_c[i];
    } else {
        a = 0;
        b = 0;
        c = 0;
    }
}

