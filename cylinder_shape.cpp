
#include "cylinder_shape.h"
#include "math.h"

CylinderShape::CylinderShape(float radius, float height)
    : m_radius(radius)
    , m_height(height)
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
    for (int j = 0; j < steps; j++) {
        float angle = dangle * (float) j;
        float cosa = cos(angle * 3.1415926535 / 180.0);
        float cosb = cos((angle + dangle) * 3.1415926535 / 180.0);
        float sina = sin(angle * 3.1415926535 / 180.0);
        float sinb = sin((angle + dangle) * 3.1415926535 / 180.0);
        float xa0 = m_radius * cosa;
        float xb0 = m_radius * cosb;
        float za0 = m_radius * sina;
        float zb0 = m_radius * sinb;
        add_face({xa0, -dy, za0}, {xb0, -dy, zb0}, {xb0, dy, zb0}, {xa0, dy, za0}, true);
        add_face({xa0, -dy, za0}, {0.0, -dy, 0.0}, {xb0, -dy, zb0}, true);
        add_face({xa0, dy, za0}, {0.0, dy, 0.0}, {xb0, dy, zb0}, false);
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

