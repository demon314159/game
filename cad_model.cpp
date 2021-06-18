//
// cad_model.cpp
//
#include "cad_model.h"
#include <math.h>

#define VERBOSE

CadModel::CadModel(const VrmlInterface& vrml_interface)
    : m_facet_count(0)
    , m_facet_v1(NULL)
    , m_facet_v2(NULL)
    , m_facet_v3(NULL)
    , m_facet_color(NULL)
{
    printf("CadModel::CadModel(vrml)\n");
    m_facet_count = vrml_interface.facets();
    if (m_facet_count > 0) {
        m_facet_v1 = new float3[m_facet_count];
        m_facet_v2 = new float3[m_facet_count];
        m_facet_v3 = new float3[m_facet_count];
        m_facet_color = new float3[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            int3 v = vrml_interface.facet_points(i);
            int m = vrml_interface.facet_material(i);
            m_facet_v1[i] = vrml_interface.point(v.v1);
            m_facet_v2[i] = vrml_interface.point(v.v2);
            m_facet_v3[i] = vrml_interface.point(v.v3);
            m_facet_color[i] = vrml_interface.ambient_color(m);
        }
    }
}

CadModel::CadModel(const StlInterface& stl_interface, const PaintCan& paint_can)
{
    printf("CadModel::CadModel(stl, paint(%8.6f, %8.6f, %8.6f))\n", paint_can.ambient_color().v1, paint_can.ambient_color().v2, paint_can.ambient_color().v3);
    m_facet_count = stl_interface.facets();
    if (m_facet_count > 0) {
        m_facet_v1 = new float3[m_facet_count];
        m_facet_v2 = new float3[m_facet_count];
        m_facet_v3 = new float3[m_facet_count];
        m_facet_color = new float3[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_facet_v1[i] = stl_interface.facet_v1(i);
            m_facet_v2[i] = stl_interface.facet_v2(i);
            m_facet_v3[i] = stl_interface.facet_v3(i);
            m_facet_color[i] = paint_can.ambient_color();
        }
    }
}

CadModel::~CadModel()
{
    printf("~CadModel::CadModel()\n");
    if (m_facet_v1 != NULL)
        delete [] m_facet_v1;
    if (m_facet_v2 != NULL)
        delete [] m_facet_v2;
    if (m_facet_v3 != NULL)
        delete [] m_facet_v3;
    if (m_facet_color != NULL)
        delete [] m_facet_color;
}

int CadModel::facets() const
{
    return m_facet_count;
}

float3 CadModel::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v1[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v2[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v3[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_color(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_color[facet_ix];
    else
        return float3{.0, 0.0, 0.0};
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

