
#include "curve_shape.h"
#include "radial.h"
#include <cstddef>

CurveShape::CurveShape(const Curve& c1, float z1, const Curve& c2, float z2)
    : m_count_mode(true)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape(c1, z1, c2, z2);
    m_count_mode = false;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape(c1, z1, c2, z2);
    }
}

CurveShape::CurveShape(const Curve& c1, float z1, bool flip)
    : m_count_mode(true)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape(c1, z1, flip);
    m_count_mode = false;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape(c1, z1, flip);
    }
}

CurveShape::~CurveShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CurveShape::facets() const
{
    return m_facet_count;
}

Facet CurveShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CurveShape::define_shape(const Curve& c1, float z1, const Curve& c2, float z2)
{
    if (c1.steps() != c2.steps())
        return;
    for (int i = 1; i < c1.steps(); i++) {
        float xa0 = c1.x(i - 1);
        float ya0 = c1.y(i - 1);
        float xb0 = c2.x(i - 1);
        float yb0 = c2.y(i - 1);
        float xa1 = c1.x(i);
        float ya1 = c1.y(i);
        float xb1 = c2.x(i);
        float yb1 = c2.y(i);
        add_face({xa0, ya0, z1}, {xb0, yb0, z2}, {xb1, yb1, z2}, {xa1, ya1, z1});
    }
}

void CurveShape::define_shape(const Curve& c1, float z1, bool flip)
{
    float xc = 0.0;
    float yc = 0.0;

    for (int i = 0; i < c1.steps(); i++) {
        xc += c1.x(i);
        yc += c1.y(i);
    }
    xc /= (float) c1.steps();
    yc /= (float) c1.steps();

    for (int i = 1; i < c1.steps(); i++) {
        float x0 = c1.x(i - 1);
        float y0 = c1.y(i - 1);
        float x1 = c1.x(i);
        float y1 = c1.y(i);
        add_face({x0, y0, z1}, {xc, yc, z1}, {x1, y1, z1}, flip);
    }
}

void CurveShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void CurveShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


