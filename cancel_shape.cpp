
#include "cancel_shape.h"
#include <cstddef>

CancelShape::CancelShape(float width)
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

CancelShape::~CancelShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CancelShape::facets() const
{
    return m_facet_count;
}

Facet CancelShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CancelShape::define_shape()
{
    float x0 = -m_width / 2;
    float x1 = -m_width / 2 + m_width / 6;
    float x5 = m_width / 2 - m_width / 6;
    float x6 = m_width / 2;
    add_face({x0, x5, 0.0}, {x1, x6, 0.0}, {x6, x1, 0.0}, {x5, x0, 0.0});
    add_face({x0, x1, 0.0}, {x1, x0, 0.0}, {x6, x5, 0.0}, {x5, x6, 0.0});
}

void CancelShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4)
{
    add_face(v1, v2, v3);
    add_face(v1, v3, v4);
}

void CancelShape::add_face(Float3 v1, Float3 v2, Float3 v3)
{
    if (!m_count_mode) {
        // Do one side of face
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        m_facet[m_facet_count].v1 = v1;
        m_facet[m_facet_count].v2 = v3;
        m_facet[m_facet_count].v3 = v2;
        ++m_facet_count;
        // Do the other side of face
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        m_facet[m_facet_count].v1 = v1;
        m_facet[m_facet_count].v2 = v2;
        m_facet[m_facet_count].v3 = v3;
        ++m_facet_count;
    } else {
        m_facet_count += 2;
    }
}


