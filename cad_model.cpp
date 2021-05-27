//
// cad_model.cpp
//
#include "cad_model.h"

#define PRINTY

CadModel::CadModel(const QString& file_name)
    : m_vertices(0)
    , m_facets(0)
    , m_x(NULL)
    , m_y(NULL)
    , m_z(NULL)
    , m_a(NULL)
    , m_b(NULL)
    , m_c(NULL)
{
    m_x = new double[MAX_VERTICES];
    m_y = new double[MAX_VERTICES];
    m_z = new double[MAX_VERTICES];
    m_a = new int[MAX_FACETS];
    m_b = new int[MAX_FACETS];
    m_c = new int[MAX_FACETS];
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
#ifdef PRINTY
        printf("Close file '%s'\n", file_name.toLatin1().data());
        printf("m_vertices = %d\n", m_vertices);
        printf("m_facets = %d\n", m_facets);
#endif
    }
}

CadModel::~CadModel()
{
    delete[] m_x;
    delete[] m_y;
    delete[] m_z;
    delete[] m_a;
    delete[] m_b;
    delete[] m_c;
}

void CadModel::parse_file(FILE* ffi)
{
    char buf[512];
    char* ptr;
    bool vertex_flag = false;
    bool facet_flag = false;

    ptr = fgets(buf, 512, ffi);
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
        } else {
            vertex_flag = (0 == strncmp(buf, "point [", 7)) ? true : false;
            facet_flag = (0 == strncmp(buf, "coordIndex [", 12)) ? true : false;
        }
        ptr = fgets(buf, 512, ffi);
    }
}

void CadModel::parse_vertex_line(char* buf)
{
    double x, y, z;
    int res, num, len;
#ifdef PRINTY
//    printf("parse_vertex_line: %s", buf);
#endif
    len = strlen(buf);
    res = sscanf(buf, "%lf %lf %lf%n", &x, &y, &z, &num);
#ifdef PRINTY
//    printf("  len = %d, res = %d, x = %lf, y = %lf, z = %lf, num = %d\n", len, res, x, y, z, num);
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
    int a, b, c, d;
    int res, num, len;
#ifdef PRINTY
//    printf("parse_facet_line: %s", buf);
#endif
    len = strlen(buf);
    res = sscanf(buf, "%d, %d, %d, %d%n", &a, &b, &c, &d, &num);
#ifdef PRINTY
//    printf("  len = %d, res = %d, a = %d, b = %d, c = %d, d = %d, num = %d\n", len, res, a, b, c, d, num);
#endif
    if ((res == 4) && (d == -1)) {
        add_facet(a, b, c);
        if (buf[num] == ',' && (num < (len - 3))) {
            parse_facet_line(buf + num + 1);
        }
    }
}

void CadModel::add_vertex(double x, double y, double z)
{
    if (m_vertices < MAX_VERTICES) {
        m_x[m_vertices] = x;
        m_y[m_vertices] = y;
        m_z[m_vertices] = z;
        ++m_vertices;
    }
}

void CadModel::add_facet(int a, int b, int c)
{
    if (m_facets < MAX_FACETS) {
        m_a[m_facets] = a;
        m_b[m_facets] = b;
        m_c[m_facets] = c;
        ++m_facets;
    }
}

int CadModel::vertices() const
{
    return m_vertices;
}

int CadModel::facets() const
{
    return m_facets;
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

