
#include "arrow_shape.h"
#include "element.h"
#include <cstddef>

ArrowShape::ArrowShape(float length, float width, int orientation)
    : m_length(length)
    , m_width(width)
    , m_orientation(orientation)
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

ArrowShape::~ArrowShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int ArrowShape::facets() const
{
    return m_facet_count;
}

Facet ArrowShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void ArrowShape::define_shape()
{
    if (m_orientation == ARROW_UP || m_orientation == ARROW_DOWN) {
        float x0 = -m_width / 2;
        float x1 = -m_width / 4;
        float x2 = m_width / 4;
        float x3 = m_width / 2;
        float y0 = -Element::dimh * m_length / 2;
        float y1 = Element::dimh * m_length / 2;
        if (m_orientation == ARROW_UP) {  // Up arrow
            add_face({x0, 0.0, 0.0}, {x3, 0.0, 0.0}, {0.0, y1, 0.0});
            add_face({x1, 0.0, 0.0}, {x1, y0, 0.0}, {x2, y0, 0.0}, {x2, 0.0, 0.0});
        } else { // Down arrow
            add_face({x0, 0.0, 0.0}, {x3, 0.0, 0.0}, {0.0, y0, 0.0});
            add_face({x1, y1, 0.0}, {x1, 0.0, 0.0}, {x2, 0.0, 0.0}, {x2, y1, 0.0});
        }
    } else {
        float y0 = -Element::dimh * m_width / 2;
        float y1 = -Element::dimh * m_width / 4;
        float y2 = Element::dimh * m_width / 4;
        float y3 = Element::dimh * m_width / 2;
        float x0 = -m_length / 2;
        float x1 = m_length / 2;
        if (m_orientation == ARROW_LEFT) { // Left arrow
            add_face({0.0, y0, 0.0}, {0.0, y3, 0.0}, {x0, 0.0, 0.0});
            add_face({0.0, y1, 0.0}, {x1, y1, 0.0}, {x1, y2, 0.0}, {0.0, y2, 0.0});
        } else {  // Right arrow
            add_face({0.0, y0, 0.0}, {0.0, y3, 0.0}, {x1, 0.0, 0.0});
            add_face({x0, y1, 0.0}, {0.0, y1, 0.0}, {0.0, y2, 0.0}, {x0, y2, 0.0});
        }
    }
}

void ArrowShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4)
{
    add_face(v1, v2, v3);
    add_face(v1, v3, v4);
}

void ArrowShape::add_face(Float3 v1, Float3 v2, Float3 v3)
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


