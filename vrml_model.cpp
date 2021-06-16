//
// vrml_model.cpp
//
#include "vrml_model.h"
#include <math.h>

#define VERBOSE

VrmlModel::VrmlModel(const QString& file_name)
    : CadModel()
    , m_vi(file_name)
{
#ifdef VERBOSE
    printf("VrmlModel(%s)\n", file_name.toLatin1().data());

    if (m_vi.file_is_valid())
        printf("Successful parse of VRML\n");
    else
        printf("<<< Parse of VRML failed >>>\n");
    printf("Parse error message: '%s'\n", m_vi.error_message().toLatin1().data());
    printf("%d materials, %d points, %d facets\n", m_vi.materials(), m_vi.points(), m_vi.facets());
#endif
}

VrmlModel::~VrmlModel()
{
#ifdef VERBOSE
    printf("~VrmlModel()\n");
#endif
}

int VrmlModel::facets() const
{
    return m_vi.facets();
}

float3 VrmlModel::facet_v1(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v1);
}

float3 VrmlModel::facet_v2(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v2);
}

float3 VrmlModel::facet_v3(int facet_ix) const
{
    int3 v = m_vi.facet_points(facet_ix);
    return m_vi.point(v.v3);
}

float3 VrmlModel::facet_color(int facet_ix) const
{
    int v = m_vi.facet_material(facet_ix);
    return m_vi.ambient_color(v);
}

