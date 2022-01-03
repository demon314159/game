
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
    float x0 = -m_dimx / 2;
    float x1 = x0 + 1 * m_dimx / 6;
    float x2 = x0 + 2 * m_dimx / 6;
    float x4 = x0 + 4 * m_dimx / 6;
    float x5 = x0 + 5 * m_dimx / 6;
    float x6 = x0 + m_dimx;

    float y0 = -m_dimy / 3;
    float y1_5 = -m_dimy / 6;
    float y4_5 = m_dimy / 6;
    float y6 = m_dimy / 3.0;

    float z0 = -m_dimz / 2;
    float z1_5 = -m_dimz / 4;
    float z4_5 = m_dimz / 4;
    float z6 = m_dimz / 2;

    float t0 =   4 * m_dimb / 4;
    float t1_5 = 5 * m_dimb / 4;
    float t4_5 = 7 * m_dimb / 4;
    float t6 =   8 * m_dimb /4;
    // partial shape 1 top and bottom
    add_face({x0, y6 + t1_5, z0}, {x0, y1_5 + t6, z4_5}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2 - m_dimb, y6 + t1_5, z0});
    add_face({x0, y6, z0}, {x0, y1_5, z4_5}, {x2, y1_5, z4_5}, {x2, y6, z0}, true);
    // left and right
    add_face({x0, y6 + t1_5, z0}, {x0, y1_5 + t6, z4_5}, {x0, y1_5, z4_5}, {x0, y6, z0}, true);
    add_face({x2 - m_dimb, y6 + t1_5, z0}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2, y1_5, z4_5}, {x2, y6, z0});
    // front and back
    add_face({x0, y1_5 + t6, z4_5}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2, y1_5, z4_5}, {x0, y1_5, z4_5}, true);
    add_face({x0, y6 + t1_5, z0}, {x2 - m_dimb, y6 + t1_5, z0}, {x2, y6, z0}, {x0, y6, z0});

    // partial shape 1 top and bottom
    add_face({x0, y1_5 + t0, z4_5}, {x0, y0 + t1_5, z6}, {x2 - m_dimb, y0 + t1_5, z6}, {x2 - m_dimb, y1_5 + t0, z4_5});
    add_face({x0, y1_5, z4_5}, {x0, y0, z6}, {x2, y0, z6}, {x2, y1_5, z4_5}, true);
    // left and right
    add_face({x0, y1_5 + t0, z4_5}, {x0, y0 + t1_5, z6}, {x0, y0, z6}, {x0, y1_5, z4_5}, true);
    add_face({x2 - m_dimb, y1_5 + t0, z4_5}, {x2 - m_dimb, y0 + t1_5, z6}, {x2, y0, z6}, {x2, y1_5, z4_5});
    // front and back
    add_face({x0, y0 + t1_5, z6}, {x2 - m_dimb, y0 + t1_5, z6}, {x2, y0, z6}, {x0, y0, z6}, true);
    // The back face is always hidden

    // partial shape 2 top and bottom
    add_face({x4 + m_dimb, y6 + t1_5, z0}, {x4 + m_dimb, y1_5 + t6, z4_5}, {x6, y1_5 + t6, z4_5}, {x6, y6 + t1_5, z0});
    add_face({x4, y6, z0}, {x4, y1_5, z4_5}, {x6, y1_5, z4_5}, {x6, y6, z0}, true);
    // left and right
    add_face({x4 + m_dimb, y6 + t1_5, z0}, {x4 + m_dimb, y1_5 + t6, z4_5}, {x4, y1_5, z4_5}, {x4, y6, z0}, true);
    add_face({x6, y6 + t1_5, z0}, {x6, y1_5 + t6, z4_5}, {x6, y1_5, z4_5}, {x6, y6, z0});
    // front and back
    add_face({x4 + m_dimb, y1_5 + t6, z4_5}, {x6, y1_5 + t6, z4_5}, {x6, y1_5, z4_5}, {x4, y1_5, z4_5}, true);
    add_face({x4 + m_dimb, y6 + t1_5, z0}, {x6, y6 + t1_5, z0}, {x6, y6, z0}, {x4, y6, z0});

    // partial shape 2 top and bottom
    add_face({x4 + m_dimb, y1_5 + t0, z4_5}, {x4 + m_dimb, y0 + t1_5, z6}, {x6, y0 + t1_5, z6}, {x6, y1_5 + t0, z4_5});
    add_face({x4, y1_5, z4_5}, {x4, y0, z6}, {x6, y0, z6}, {x6, y1_5, z4_5}, true);
    // left and right
    add_face({x4 + m_dimb, y1_5 + t0, z4_5}, {x4 + m_dimb, y0 + t1_5, z6}, {x4, y0, z6}, {x4, y1_5, z4_5}, true);
    add_face({x6, y1_5 + t0, z4_5}, {x6, y0 + t1_5, z6}, {x6, y0, z6}, {x6, y1_5, z4_5});
    // front and back
    add_face({x4 + m_dimb, y0 + t1_5, z6}, {x6, y0 + t1_5, z6}, {x6, y0, z6}, {x4, y0, z6}, true);
    // The back face is always hidden

    // partial shape 3 top and bottom
    add_face({x1 + m_dimb, y6 + t4_5, z0}, {x1 + m_dimb, y4_5 + t6, z1_5}, {x5 - m_dimb, y4_5 + t6, z1_5}, {x5 - m_dimb, y6 + t4_5, z0});
    add_face({x1, y6, z0}, {x1, y4_5, z1_5}, {x5, y4_5, z1_5}, {x5, y6, z0}, true);
    // left and right
    add_face({x1 + m_dimb, y6 + t4_5, z0}, {x1 + m_dimb, y4_5 + t6, z1_5}, {x1, y4_5, z1_5}, {x1, y6, z0}, true);
    add_face({x5 - m_dimb, y6 + t4_5, z0}, {x5 - m_dimb, y4_5 + t6, z1_5}, {x5, y4_5, z1_5}, {x5, y6, z0});
    // front and back
    add_face({x1 + m_dimb, y4_5 + t6, z1_5}, {x5 - m_dimb, y4_5 + t6, z1_5}, {x5, y4_5, z1_5}, {x1, y4_5, z1_5}, true);
    add_face({x1 + m_dimb, y6 + t4_5, z0}, {x5 - m_dimb, y6 + t4_5, z0}, {x5, y6, z0}, {x1, y6, z0});

    // partial shape 3 top and bottom
    add_face({x1 + m_dimb, y4_5 + t0, z1_5}, {x1 + m_dimb, y0 + t4_5, z6}, {x5 - m_dimb, y0 + t4_5, z6}, {x5 - m_dimb, y4_5 + t0, z1_5});
    add_face({x1, y4_5, z1_5}, {x1, y0, z6}, {x5, y0, z6}, {x5, y4_5, z1_5}, true);
    // left and right
    add_face({x1 + m_dimb, y4_5 + t0, z1_5}, {x1 + m_dimb, y0 + t4_5, z6}, {x1, y0, z6}, {x1, y6, z0}, true);
    add_face({x5 - m_dimb, y4_5 + t0, z1_5}, {x5 - m_dimb, y0 + t4_5, z6}, {x5, y0, z6}, {x5, y6, z0});
    // front and back
    add_face({x1 + m_dimb, y0 + t4_5, z6}, {x5 - m_dimb, y0 + t4_5, z6}, {x5, y0, z6}, {x1, y0, z6}, true);
    // The back face is always hidden
    add_face({x1 + m_dimb, y6 + t4_5, z0}, {x5 - m_dimb, y6 + t4_5, z0}, {x5, y6, z0}, {x1, y6, z0});
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


