
#include "cube_shape.h"
#include <cstddef>

CubeShape::CubeShape(float dimx, float dimy, float dimz)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
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

CubeShape::~CubeShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CubeShape::facets() const
{
    return m_facet_count;
}

Facet CubeShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CubeShape::define_shape()
{
    // faces
    add_face(0x0, 0x1, 0x3, 0x2);
    add_face(0x4, 0x5, 0x7, 0x6, true);
    add_face(0x0, 0x1, 0x5, 0x4, true);
    add_face(0x2, 0x3, 0x7, 0x6);
    add_face(0x0, 0x4, 0x6, 0x2, true);
    add_face(0x1, 0x5, 0x7, 0x3);
}

void CubeShape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void CubeShape::add_face(int v1, int v2, int v3, bool flip)
{
    if (!m_count_mode) {
        m_facet[m_facet_count].animation_id = 0.0;
        m_facet[m_facet_count].color = {1.0, 1.0, 1.0};
        if (flip) {
            m_facet[m_facet_count].v1 = decode_vertex(v1);
            m_facet[m_facet_count].v2 = decode_vertex(v3);
            m_facet[m_facet_count].v3 = decode_vertex(v2);
        } else {
            m_facet[m_facet_count].v1 = decode_vertex(v1);
            m_facet[m_facet_count].v2 = decode_vertex(v2);
            m_facet[m_facet_count].v3 = decode_vertex(v3);
        }
    }
    ++m_facet_count;
}

Float3 CubeShape::decode_vertex(int v)
{
    Float3 r;

    if (v & 0x4) {
        r.v1 = m_dimx / 2.0;
    } else {
        r.v1 = -m_dimx / 2.0;
    }
    if (v & 0x2) {
        r.v2 = m_dimy / 2.0;
    } else {
        r.v2 = -m_dimy / 2.0;
    }
    if (v & 0x1) {
        r.v3 = m_dimz / 2.0;
    } else {
        r.v3 = -m_dimz / 2.0;
    }
    return r;
}

