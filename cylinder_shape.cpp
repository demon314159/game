
#include "cylinder_shape.h"
#include "math.h"

CylinderShape::CylinderShape(float radius, float height, float upper_bevel, float lower_bevel)
    : m_radius(radius)
    , m_height(height)
    , m_upper_bevel(upper_bevel)
    , m_lower_bevel(lower_bevel)
    , m_count_mode(true)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape();
    m_count_mode = false;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape();
    }
}

CylinderShape::~CylinderShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CylinderShape::facets() const
{
    return m_facet_count;
}

Facet CylinderShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CylinderShape::define_shape()
{
    float approx_dangle = 2.0; // degrees
    int steps = round(360.0 / approx_dangle);
    float dangle = 360.0 / (float) steps;
    float dy = m_height / 2.0;
    float ub = m_upper_bevel;
    float lb = m_lower_bevel;
    for (int j = 0; j < steps; j++) {
        float angle = dangle * (float) j;
        float cosa = cos(angle * 3.1415926535 / 180.0);
        float cosb = cos((angle + dangle) * 3.1415926535 / 180.0);
        float sina = sin(angle * 3.1415926535 / 180.0);
        float sinb = sin((angle + dangle) * 3.1415926535 / 180.0);


        float xa1 = m_radius * cosa;
        float xb1 = m_radius * cosb;
        float za1 = m_radius * sina;
        float zb1 = m_radius * sinb;
        add_face({xa1, -dy + lb, za1}, {xb1, -dy + lb, zb1}, {xb1, dy - ub, zb1}, {xa1, dy - ub, za1}, true);

        float xa0 = (m_radius - lb) * cosa;
        float xb0 = (m_radius - lb) * cosb;
        float za0 = (m_radius - lb) * sina;
        float zb0 = (m_radius - lb) * sinb;
        add_face({xa0, -dy, za0}, {0.0, -dy, 0.0}, {xb0, -dy, zb0}, true);
        if (lb != 0.0) {
            add_face({xa0, -dy, za0}, {xa1, -dy + lb, za1}, {xb1, -dy + lb, zb1}, {xb0, -dy, zb0}, false);
        }

        float xa2 = (m_radius - ub) * cosa;
        float xb2 = (m_radius - ub) * cosb;
        float za2 = (m_radius - ub) * sina;
        float zb2 = (m_radius - ub) * sinb;
        add_face({xa2, dy, za2}, {0.0, dy, 0.0}, {xb2, dy, zb2}, false);
        if (ub != 0.0) {
            add_face({xa2, dy, za2}, {xa1, dy - ub, za1}, {xb1, dy - ub, zb1}, {xb2, dy, zb2}, true);
        }
    }
}

void CylinderShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void CylinderShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
{
    if (!m_count_mode) {
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        if (flip) {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v3;
            m_facet[m_facet_count].v3 = v2;
        } else {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v2;
            m_facet[m_facet_count].v3 = v3;
        }
    }
    ++m_facet_count;
}

