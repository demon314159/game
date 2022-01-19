
#include "done_shape.h"
#include <cstddef>

DoneShape::DoneShape(float width)
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

DoneShape::~DoneShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int DoneShape::facets() const
{
    return m_facet_count;
}

Facet DoneShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void DoneShape::define_shape()
{
    float dz = 0.01;
    float x0 = -m_width / 2;
    float x1 = -m_width / 2 + m_width / 6;
    float x2 = -m_width / 2 + 2 * m_width / 6;
    float x3 = 0.0;
    float x4 = m_width / 2 - 2 * m_width / 6;
    float x5 = m_width / 2 - m_width / 6;
    float x6 = m_width / 2;
    // Front face
    add_face({x0, x2, dz}, {x1, x3, dz}, {x3, x1, dz}, {x2, x0, dz}, true);
    add_face({x1, x1, dz}, {x5, x6, dz}, {x6, x5, dz}, {x2, x0, dz}, true);
    // back face should be x reversed
    add_face({x6, x2, -dz}, {x5, x3, -dz}, {x3, x1, -dz}, {x4, x0, -dz}, true);
    add_face({x5, x1, -dz}, {x1, x6, -dz}, {x0, x5, -dz}, {x4, x0, -dz}, true);
}

void DoneShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void DoneShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


