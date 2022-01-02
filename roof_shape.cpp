
#include "roof_shape.h"
#include <cstddef>

RoofShape::RoofShape(float dimx, float dimy, float dimz, float dimb)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
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

RoofShape::~RoofShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int RoofShape::facets() const
{
    return m_facet_count;
}

Facet RoofShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void RoofShape::define_shape()
{
    // faces
    float x0 = -m_dimx / 2.0;
    float x1 = x0 + m_dimx / 3.0;
    float x2 = x0 + 2 * m_dimx / 3.0;
    float x3 = x0 + m_dimx;
    float z0 = -m_dimz / 2.0;
    float z1 = 0.0;
    float z2 = m_dimz / 2.0;
    float y0 = -m_dimy / 3.0;
    float y1 = 0.0;
    float y2 = m_dimy / 3.0;

    // top and bottom
    add_face({x0, y2 + m_dimb, z0}, {x0, y0 + 2 * m_dimb, z2}, {x1, y0 + 2 * m_dimb, z2}, {x1, y2 + m_dimb, z0});
    add_face({x0, y2, z0}, {x0, y0, z2}, {x1, y0, z2}, {x1, y2, z0}, true);
    // left and right
    add_face({x0, y2 + m_dimb, z0}, {x0, y0 + 2 * m_dimb, z2}, {x0, y0, z2}, {x0, y2, z0}, true);
    add_face({x1, y2 + m_dimb, z0}, {x1, y0 + 2 * m_dimb, z2}, {x1, y0, z2}, {x1, y2, z0});
    // front and back
    add_face({x0, y0 + 2 * m_dimb, z2}, {x1, y0 + 2 * m_dimb, z2}, {x1, y0, z2}, {x0, y0, z2}, true);
    add_face({x0, y2 + m_dimb, z0}, {x1, y2 + m_dimb, z0}, {x1, y2, z0}, {x0, y2, z0});

    // top and bottom
    add_face({x2, y2 + m_dimb, z0}, {x2, y0 + 2 * m_dimb, z2}, {x3, y0 + 2 * m_dimb, z2}, {x3, y2 + m_dimb, z0});
    add_face({x2, y2, z0}, {x2, y0, z2}, {x3, y0, z2}, {x3, y2, z0}, true);
    // left and right
    add_face({x2, y2 + m_dimb, z0}, {x2, y0 + 2 * m_dimb, z2}, {x2, y0, z2}, {x2, y2, z0}, true);
    add_face({x3, y2 + m_dimb, z0}, {x3, y0 + 2 * m_dimb, z2}, {x3, y0, z2}, {x3, y2, z0});
    // front and back
    add_face({x2, y0 + 2 * m_dimb, z2}, {x3, y0 + 2 * m_dimb, z2}, {x3, y0, z2}, {x2, y0, z2}, true);
    add_face({x2, y2 + m_dimb, z0}, {x3, y2 + m_dimb, z0}, {x3, y2, z0}, {x2, y2, z0});


//    add_face({x0, y2 + m_dimb, z0}, {x0, y0 + 2 * m_dimb, z2}, {x1, y0 + 2 * m_dimb, z2}, {x1, y2 + m_dimb, z0});
//    add_face({x0, y2, z0}, {x0, y0, z2}, {x1, y0, z2}, {x1, y2, z0}, true);
}

void RoofShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void RoofShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


