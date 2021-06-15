//
// cad_model.cpp
//
#include "cad_model.h"
#include <math.h>

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

int CadModel::facets() const
{
    return m_vi.facets();
}

float3 CadModel::facet_v1(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v1);
}

float3 CadModel::facet_v2(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v2);
}

float3 CadModel::facet_v3(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v3);
}

float3 CadModel::facet_color(int facet_ix) const
{
    int v = m_vi.facet_material(facet_ix);
    return m_vi.ambient_color(v);
}

float3 CadModel::facet_normal(int facet_ix) const
{
    float3 p1, p2, p3;
    p1 = facet_v1(facet_ix);
    p2 = facet_v2(facet_ix);
    p3 = facet_v3(facet_ix);
    float3 va, vb;
    va.v1 = p2.v1 - p1.v1;
    va.v2 = p2.v2 - p1.v2;
    va.v3 = p2.v3 - p1.v3;
    vb.v1 = p3.v1 - p1.v1;
    vb.v2 = p3.v2 - p1.v2;
    vb.v3 = p3.v3 - p1.v3;
    float3 xp;
    xp.v1 = va.v2 * vb.v3 - vb.v2 * va.v3;
    xp.v2 = vb.v1 * va.v3 - va.v1 * vb.v3;
    xp.v3 = va.v1 * vb.v2 - vb.v1 * va.v2;
    return xp;
}

