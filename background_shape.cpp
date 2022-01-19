
#include "background_shape.h"
#include <cstddef>

BackgroundShape::BackgroundShape(float width)
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

BackgroundShape::~BackgroundShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int BackgroundShape::facets() const
{
    return m_facet_count;
}

Facet BackgroundShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void BackgroundShape::define_shape()
{
    float x0 = -m_width / 2;
    float x6 = m_width / 2;
    add_face({x0, x0, 0}, {x0, x6, 0}, {x6, x6, 0}, {x6, x0, 0});
}

void BackgroundShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4)
{
    add_face(v1, v2, v3);
    add_face(v1, v3, v4);
}

void BackgroundShape::add_face(Float3 v1, Float3 v2, Float3 v3)
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


