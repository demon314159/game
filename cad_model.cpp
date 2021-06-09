//
// cad_model.cpp
//
#include "cad_model.h"

#define VERBOSE

CadModel::CadModel(const QString& file_name)
    : m_vi(file_name)
{
#ifdef VERBOSE
    printf("CadModel(%s)\n", file_name.toLatin1().data());

    if (m_vi.file_is_valid())
        printf("Successful parse of VRML\n");
    else
        printf("<<< Parse of VRML failed >>>\n");
    printf("Parse error message: '%s'\n", m_vi.error_message().toLatin1().data());
    printf("%d materials, %d points, %d facets\n", m_vi.materials(), m_vi.points(), m_vi.facets());
#endif
}

CadModel::~CadModel()
{
#ifdef VERBOSE
    printf("~CadModel()\n");
#endif
}

int CadModel::vertices() const
{
    return m_vi.points();
}

int CadModel::facets() const
{
    return m_vi.facets();
}

void CadModel::get_vertex(int ix, float& x, float& y, float& z) const
{
    float3 v = m_vi.point(ix);
    x = v.v1;
    y = v.v2;
    z = v.v3;
}

void CadModel::get_facet(int ix, int& a, int& b, int& c) const
{
    int3 v = m_vi.facet_points(ix);
    a = v.v1;
    b = v.v2;
    c = v.v3;
}




#ifdef NEVERMORE
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
#endif

