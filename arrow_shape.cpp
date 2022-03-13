
#include "arrow_shape.h"
#include <cstddef>

ArrowShape::ArrowShape(float length, float width, int orientation, bool just_one_face)
    : m_length(length)
    , m_width(width)
    , m_orientation(orientation)
    , m_just_one_face(just_one_face)
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
    float dz = m_just_one_face ? 0.0 : 0.01;
    if (m_orientation == ARROW_UP || m_orientation == ARROW_DOWN) {
        float x0 = -m_width / 2;
        float x1 = -m_width / 4;
        float x2 = m_width / 4;
        float x3 = m_width / 2;
        float y0 = -m_length / 2;
        float y1 = m_length / 2;
        if (m_orientation == ARROW_UP) {  // Up arrow
            // Front face
            add_face({x0, 0.0, dz}, {x3, 0.0, dz}, {0.0, y1, dz});
            add_face({x1, 0.0, dz}, {x1, y0, dz}, {x2, y0, dz}, {x2, 0.0, dz});
            // Back face
            if (!m_just_one_face) {
                add_face({x0, 0.0, -dz}, {x3, 0.0, -dz}, {0.0, y1, -dz}, true);
                add_face({x1, 0.0, -dz}, {x1, y0, -dz}, {x2, y0, -dz}, {x2, 0.0, -dz}, true);
            }
        } else { // Down arrow
            // Front face
            add_face({x0, 0.0, dz}, {x3, 0.0, dz}, {0.0, y0, dz}, true);
            add_face({x1, y1, dz}, {x1, 0.0, dz}, {x2, 0.0, dz}, {x2, y1, dz});
            // Back face
            if (!m_just_one_face) {
                add_face({x0, 0.0, -dz}, {x3, 0.0, -dz}, {0.0, y0, -dz});
                add_face({x1, y1, -dz}, {x1, 0.0, -dz}, {x2, 0.0, -dz}, {x2, y1, -dz}, true);
            }
        }
    } else {
        float y0 = -m_width / 2;
        float y1 = -m_width / 4;
        float y2 = m_width / 4;
        float y3 = m_width / 2;
        float x0 = -m_length / 2;
        float x1 = m_length / 2;
        if (m_orientation == ARROW_LEFT) { // Left arrow
            // Front face
            add_face({0.0, y0, dz}, {0.0, y3, dz}, {x0, 0.0, dz});
            add_face({0.0, y1, dz}, {x1, y1, dz}, {x1, y2, dz}, {0.0, y2, dz});
            // Back face
            if (!m_just_one_face) {
                add_face({0.0, y0, -dz}, {0.0, y3, -dz}, {x0, 0.0, -dz}, true);
                add_face({0.0, y1, -dz}, {x1, y1, -dz}, {x1, y2, -dz}, {0.0, y2, -dz}, true);
            }
        } else {  // Right arrow
            // front face
            add_face({0.0, y0, dz}, {0.0, y3, dz}, {x1, 0.0, dz}, true);
            add_face({x0, y1, dz}, {0.0, y1, dz}, {0.0, y2, dz}, {x0, y2, dz});
            // Back face
            if (!m_just_one_face) {
                add_face({0.0, y0, -dz}, {0.0, y3, -dz}, {x1, 0.0, -dz});
                add_face({x0, y1, -dz}, {0.0, y1, -dz}, {0.0, y2, -dz}, {x0, y2, -dz}, true);
            }
        }
    }
}

void ArrowShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void ArrowShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


