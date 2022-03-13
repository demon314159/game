
#include "morph_shape.h"
#include <math.h>
#include <cstddef>

MorphShape::MorphShape(float width)
    : m_width(width)
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

MorphShape::~MorphShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int MorphShape::facets() const
{
    return m_facet_count;
}

Facet MorphShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void MorphShape::define_shape()
{
    define_arrow_shape(0);
    define_arrow_shape(120);
    define_arrow_shape(240);
}

void MorphShape::define_arrow_shape(float degrees)
{
    float dz = 0.0;
    float y0 = -m_width / 4;
    float y1 = -m_width / 8;
    float y2 = m_width / 8;
    float y3 = m_width / 4;
    float x0 = -m_width / 2;
    float x1 = m_width / 2;
    // front face
    add_face(degrees, {0.0, y0, dz}, {0.0, y3, dz}, {x1, 0.0, dz}, true);
    add_face(degrees, {x0, y1, dz}, {0.0, y1, dz}, {0.0, y2, dz}, {x0, y2, dz});
}

void MorphShape::add_face(float degrees, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(degrees, v1, v2, v3, flip);
    add_face(degrees, v1, v3, v4, flip);
}

void MorphShape::add_face(float degrees, Float3 v1, Float3 v2, Float3 v3, bool flip)
{
    float offset = m_width / 3;
    v1.v2 -= offset;
    v2.v2 -= offset;
    v3.v2 -= offset;
    Float3 rv1 = rotate(v1, degrees);
    Float3 rv2 = rotate(v2, degrees);
    Float3 rv3 = rotate(v3, degrees);
    if (!m_count_mode) {
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        if (flip) {
            m_facet[m_facet_count].v1 = rv1;
            m_facet[m_facet_count].v2 = rv3;
            m_facet[m_facet_count].v3 = rv2;
        } else {
            m_facet[m_facet_count].v1 = rv1;
            m_facet[m_facet_count].v2 = rv2;
            m_facet[m_facet_count].v3 = rv3;
        }
    }
    ++m_facet_count;
}

Float3 MorphShape::rotate(Float3 v, float degrees)
{
    float angle = degrees * 3.1415926536 / 180.0;
    Float3 rv;

    rv.v1 = v.v1 * cos(angle) + v.v2 * sin(angle);
    rv.v2 = -v.v1 * sin(angle) + v.v2 * cos(angle);
    rv.v3 = v.v3;
    return rv;
}
