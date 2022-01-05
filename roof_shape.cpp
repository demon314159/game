
#include "roof_shape.h"
#include <cstddef>

RoofShape::RoofShape(float dimx, float dimy, float dimz, float dimb, float thickness, bool top_faces)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
    , m_thickness(thickness)
    , m_top_faces(top_faces)
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
    float x3 = x0 + 3 * m_dimx / 6;
    float x4 = x0 + 4 * m_dimx / 6;
    float x5 = x0 + 5 * m_dimx / 6;
    float x6 = x0 + m_dimx;

    float smidge = 0.025;
    float y0 = smidge -m_dimy / 3;
    float y1_5 = smidge -m_dimy / 6;
    float y4_5 = smidge + m_dimy / 6;
    float y6 = smidge + m_dimy / 3.0;

    float z0 = -m_dimz / 2;
    float z1_5 = -m_dimz / 4;
    float z4_5 = m_dimz / 4;
    float z6 = m_dimz / 2;

    float t0 =   4 * m_thickness / 4;
    float t1_5 = 5 * m_thickness / 4;
    float t3 =   6 * m_thickness / 4;
    float t4_5 = 7 * m_thickness / 4;
    float t6 =   8 * m_thickness / 4;

    // shape 1.1 top and bottom
if (m_top_faces) {
    add_face({x0, y6 + t3, z0}, {x0, y4_5 + t6, z1_5}, {x4 - m_dimb, y4_5 + t6, z1_5}, {x4 - m_dimb, y6 + t3, z0});
} else {
    add_face({x0, y6, z0}, {x0, y4_5, z1_5}, {x4, y4_5, z1_5}, {x4, y6, z0}, true);
    // left and right
    add_face({x0, y6 + t3, z0}, {x0, y4_5 + t6, z1_5}, {x0, y4_5, z1_5}, {x0, y6, z0}, true);
    add_face({x4 - m_dimb, y6 + t3, z0}, {x4 - m_dimb, y4_5 + t6, z1_5}, {x4, y4_5, z1_5}, {x4, y6, z0});
    // front and back
    add_face({x0, y4_5 + t6, z1_5}, {x4 - m_dimb, y4_5 + t6, z1_5}, {x4, y4_5, z1_5}, {x0, y4_5, z1_5}, true);
    add_face({x0, y6 + t3, z0}, {x4 - m_dimb, y6 + t3, z0}, {x4, y6, z0}, {x0, y6, z0});
}

    // shape 1.2 top and bottom
if (m_top_faces) {
    add_face({x4 + m_dimb, y6 + t3, z0}, {x4 + m_dimb, y4_5 + t6, z1_5}, {x6, y4_5 + t6, z1_5}, {x6, y6 + t3, z0});
} else {
    add_face({x4, y6, z0}, {x4, y4_5, z1_5}, {x6, y4_5, z1_5}, {x6, y6, z0}, true);
    // left and right
    add_face({x4 + m_dimb, y6 + t3, z0}, {x4 + m_dimb, y4_5 + t6, z1_5}, {x4, y4_5, z1_5}, {x4, y6, z0}, true);
    add_face({x6, y6 + t3, z0}, {x6, y4_5 + t6, z1_5}, {x6, y4_5, z1_5}, {x6, y6, z0});
    // front and back
    add_face({x4 + m_dimb, y4_5 + t6, z1_5}, {x6, y4_5 + t6, z1_5}, {x6, y4_5, z1_5}, {x4, y4_5, z1_5}, true);
    add_face({x4 + m_dimb, y6 + t3, z0}, {x6, y6 + t3, z0}, {x6, y6, z0}, {x4, y6, z0});
}

    // shape 2.1 top and bottom
if (m_top_faces) {
    add_face({x0, y1_5 + t0, z4_5}, {x0, y0 + t3, z6}, {x4 - m_dimb, y0 + t3, z6}, {x4 - m_dimb, y1_5 + t0, z4_5});
} else {
    add_face({x0, y1_5, z4_5}, {x0, y0, z6}, {x4, y0, z6}, {x4, y1_5, z4_5}, true);
    // left and right
    add_face({x0, y1_5 + t0, z4_5}, {x0, y0 + t3, z6}, {x0, y0, z6}, {x0, y1_5, z4_5}, true);
    add_face({x4 - m_dimb, y1_5 + t0, z4_5}, {x4 - m_dimb, y0 + t3, z6}, {x4, y0, z6}, {x4, y1_5, z4_5});
    // front and back
    add_face({x0, y0 + t3, z6}, {x4 - m_dimb, y0 + t3, z6}, {x4, y0, z6}, {x0, y0, z6}, true);
    // The back face is always hidden
}

    // shape 2.2 top and bottom
if (m_top_faces) {
    add_face({x4 + m_dimb, y1_5 + t0, z4_5}, {x4 + m_dimb, y0 + t3, z6}, {x6, y0 + t3, z6}, {x6, y1_5 + t0, z4_5});
} else {
    add_face({x4, y1_5, z4_5}, {x4, y0, z6}, {x6, y0, z6}, {x6, y1_5, z4_5}, true);
    // left and right
    add_face({x4 + m_dimb, y1_5 + t0, z4_5}, {x4 + m_dimb, y0 + t3, z6}, {x4, y0, z6}, {x4, y1_5, z4_5}, true);
    add_face({x6, y1_5 + t0, z4_5}, {x6, y0 + t3, z6}, {x6, y0, z6}, {x6, y1_5, z4_5});
    // front and back
    add_face({x4 + m_dimb, y0 + t3, z6}, {x6, y0 + t3, z6}, {x6, y0, z6}, {x4, y0, z6}, true);
    // The back face is always hidden
}

    // shape 3.1 top and bottom
if (m_top_faces) {
    add_face({x0, y4_5 + t0, z1_5}, {x0, y1_5 + t6, z4_5}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2 - m_dimb, y4_5 + t0, z1_5});
} else {
    add_face({x0, y4_5, z1_5}, {x0, y1_5, z4_5}, {x4, y1_5, z4_5}, {x4, y4_5, z1_5}, true);
    // left and right
    add_face({x0, y4_5 + t0, z1_5}, {x0, y1_5 + t6, z4_5}, {x0, y1_5, z4_5}, {x0, y4_5, z1_5}, true);
    add_face({x2 - m_dimb, y4_5 + t0, z1_5}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2, y1_5, z4_5}, {x2, y4_5, z1_5});
    // front and back
    add_face({x0, y1_5 + t6, z4_5}, {x2 - m_dimb, y1_5 + t6, z4_5}, {x2, y1_5, z4_5}, {x0, y1_5, z4_5}, true);
    // The back face is always hidden
}

    // shape 3.2 top and bottom
if (m_top_faces) {
    add_face({x2 + m_dimb, y4_5 + t0, z1_5}, {x2 + m_dimb, y1_5 + t6, z4_5}, {x6, y1_5 + t6, z4_5}, {x6, y4_5 + t0, z1_5});
} else {
    add_face({x2, y4_5, z1_5}, {x2, y1_5, z4_5}, {x6, y1_5, z4_5}, {x6, y4_5, z1_5}, true);
    // left and right
    add_face({x2 + m_dimb, y4_5 + t0, z1_5}, {x2 + m_dimb, y1_5 + t6, z4_5}, {x2, y1_5, z4_5}, {x2, y4_5, z1_5}, true);
    add_face({x6, y4_5 + t0, z1_5}, {x6, y1_5 + t6, z4_5}, {x6, y1_5, z4_5}, {x6, y4_5, z1_5});
    // front and back
    add_face({x2 + m_dimb, y1_5 + t6, z4_5}, {x6, y1_5 + t6, z4_5}, {x6, y1_5, z4_5}, {x2, y1_5, z4_5}, true);
}
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


