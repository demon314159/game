
#include "roof_shape.h"
#include <cstddef>

RoofShape::RoofShape(float dimx, float dimy, float dimz, float dimb, float dimt)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
    , m_dimt(dimt)
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
    float x1_5 = x0 + m_dimx / 4;
    float x3 = x0 + m_dimx / 2;
    float x4_5 = x0 + 3 * m_dimx / 4;
    float x6 = x0 + m_dimx;

    float smidge = 0.025;
    float y0 = smidge -m_dimy / 3;
    float y1_5 = smidge -m_dimy / 6;
    float y4_5 = smidge + m_dimy / 6;
    float y6 = smidge + m_dimy / 3.0;
    float underhang = smidge;

    float z0 = -m_dimz / 2;
    float z1_5 = -m_dimz / 4;
    float z4_5 = m_dimz / 4;
    float z6 = m_dimz / 2;

    float t0 =   m_dimt;
    float t3 =   3 * m_dimt / 2;
    float t6 =   2 * m_dimt;

    define_lower_half(x0, x3, y6, y4_5, z0, z1_5, t3, t6, underhang);
    define_lower_half(x3, x6, y6, y4_5, z0, z1_5, t3, t6, underhang);
    define_right_half(x0, x1_5, y4_5, y1_5, z1_5, z4_5, t0, t6, underhang);
    define_lower_half(x1_5, x4_5, y4_5, y1_5, z1_5, z4_5, t0, t6, underhang);
    define_left_half(x4_5, x6, y4_5, y1_5, z1_5, z4_5, t0, t6, underhang);
    define_upper_half(x0, x3, y1_5, y0, z4_5, z6, t0, t3, underhang);
    define_upper_half(x3, x6, y1_5, y0, z4_5, z6, t0, t3, underhang);

#ifdef NEVERMORE
    // shape 1.1 top and bottom
    add_face({x0, y6 + t3, z0}, {x0, y4_5 + t6, z1_5}, {x4 - m_dimb, y4_5 + t6, z1_5}, {x4 - m_dimb, y6 + t3, z0});
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
#endif
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

void RoofShape::define_lower_half(float x1, float x2, float y1, float y2, float z1, float z2, float t1, float t2, float underhang)
{
    float k = 2 * m_dimb / 3;
    // top and bottom
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y1 + t1, z1});
    add_face({x1, y1 - underhang, z1}, {x1, y2 - underhang, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1}, true);
    // left and right
    add_face({x1, y1 + t1 - m_dimb, z1}, {x1, y2 + t2 - m_dimb, z2}, {x1, y2 - underhang, z2}, {x1, y1 - underhang, z1}, true);
    add_face({x2, y1 + t1 - m_dimb, z1}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1});
    // front and back
    add_face({x1, y2 + t2 - m_dimb, z2}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x1, y2 - underhang, z2}, true);
    add_face({x1, y1 + t1 - m_dimb, z1}, {x2, y1 + t1 - m_dimb, z1}, {x2, y1 - underhang, z1}, {x1, y1 - underhang, z1});
    // left and right bevels
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x1, y2 + t2 - m_dimb, z2}, {x1, y1 + t1 - m_dimb, z1}, true);
    add_face({x2 - m_dimb, y1 + t1, z1}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x2, y1 + t1 - m_dimb, z1});
    // front and back bevels
    add_face({x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x1, y2 + t2 - m_dimb, z2}, true);
    add_face({x1 + m_dimb, y1 + t1, z1}, {x2 - m_dimb, y1 + t1, z1}, {x2, y1 + t1 - m_dimb, z1}, {x1, y1 + t1 - m_dimb, z1});
}

void RoofShape::define_upper_half(float x1, float x2, float y1, float y2, float z1, float z2, float t1, float t2, float underhang)
{
    // top and bottom
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2, z2}, {x2 - m_dimb, y2 + t2, z2}, {x2 - m_dimb, y1 + t1, z1});
    add_face({x1, y1 - underhang, z1}, {x1, y2 - underhang, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1}, true);
    // left and right
    add_face({x1, y1 + t1 - m_dimb, z1}, {x1, y2 + t2 - m_dimb, z2}, {x1, y2 - underhang, z2}, {x1, y1 - underhang, z1}, true);
    add_face({x2, y1 + t1 - m_dimb, z1}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1});
    // front and back
    add_face({x1, y2 + t2 - m_dimb, z2}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x1, y2 - underhang, z2}, true);
    // The back face is always hidden
    // left and right bevels
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2, z2}, {x1, y2 + t2 - m_dimb, z2}, {x1, y1 + t1 - m_dimb, z1}, true);
    add_face({x2 - m_dimb, y1 + t1, z1}, {x2 - m_dimb, y2 + t2, z2}, {x2, y2 + t2 - m_dimb, z2}, {x2, y1 + t1 - m_dimb, z1});
    // front and back bevels
    add_face({x1 + m_dimb, y2 + t2, z2}, {x2 - m_dimb, y2 + t2, z2}, {x2, y2 + t2 - m_dimb, z2}, {x1, y2 + t2 - m_dimb, z2}, true);
    // The back face is always hidden
}

void RoofShape::define_left_half(float x1, float x2, float y1, float y2, float z1, float z2, float t1, float t2, float underhang)
{
    float k = 2 * m_dimb / 3;
    // top and bottom
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 + k, z2 - m_dimb}, {x2, y1 + t1, z1});
    add_face({x1, y1 - underhang, z1}, {x1, y2 - underhang, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1}, true);
    // left and right
    add_face({x1, y1 + t1 - m_dimb, z1}, {x1, y2 + t2 - m_dimb, z2}, {x1, y2 - underhang, z2}, {x1, y1 - underhang, z1}, true);
    add_face({x2, y1 + t1 - m_dimb, z1}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1});
    // front and back
    add_face({x1, y2 + t2 - m_dimb, z2}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x1, y2 - underhang, z2}, true);
    // The back face is always hidden
    // left and right bevels
    add_face({x1 + m_dimb, y1 + t1, z1}, {x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x1, y2 + t2 - m_dimb, z2}, {x1, y1 + t1 - m_dimb, z1}, true);
    add_face({x2, y1 + t1, z1}, {x2, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x2, y1 + t1 - m_dimb, z1});
    // front and back bevels
    add_face({x1 + m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x1, y2 + t2 - m_dimb, z2}, true);
    // The back face is always hidden
}

void RoofShape::define_right_half(float x1, float x2, float y1, float y2, float z1, float z2, float t1, float t2, float underhang)
{
    float k = 2 * m_dimb / 3;
    // top and bottom
    add_face({x1, y1 + t1, z1}, {x1, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y1 + t1, z1});
    add_face({x1, y1 - underhang, z1}, {x1, y2 - underhang, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1}, true);
    // left and right
    add_face({x1, y1 + t1 - m_dimb, z1}, {x1, y2 + t2 - m_dimb, z2}, {x1, y2 - underhang, z2}, {x1, y1 - underhang, z1}, true);
    add_face({x2, y1 + t1 - m_dimb, z1}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x2, y1 - underhang, z1});
    // front and back
    add_face({x1, y2 + t2 - m_dimb, z2}, {x2, y2 + t2 - m_dimb, z2}, {x2, y2 - underhang, z2}, {x1, y2 - underhang, z2}, true);
    // The back face is always hidden
    // left and right bevels
    add_face({x1, y1 + t1, z1}, {x1, y2 + t2 + k, z2 - m_dimb}, {x1, y2 + t2 - m_dimb, z2}, {x1, y1 + t1 - m_dimb, z1}, true);
    add_face({x2 - m_dimb, y1 + t1, z1}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x2, y1 + t1 - m_dimb, z1});
    // front and back bevels
    add_face({x1, y2 + t2 + k, z2 - m_dimb}, {x2 - m_dimb, y2 + t2 + k, z2 - m_dimb}, {x2, y2 + t2 - m_dimb, z2}, {x1, y2 + t2 - m_dimb, z2}, true);
    // The back face is always hidden
}

