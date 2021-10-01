
#include "brick_shape.h"
#include <cstddef>

BrickShape::BrickShape(float dimx, float dimy, float dimz, float dimb)
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
        m_facet = new facet[m_facet_count];
        m_facet_count = 0;
        define_shape();
    }
}

BrickShape::~BrickShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int BrickShape::facets() const
{
    return m_facet_count;
}

facet BrickShape::get_facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void BrickShape::define_shape()
{
    // faces
    add_face(0x04, 0x14, 0x34, 0x24);
    add_face(0x44, 0x54, 0x74, 0x64, true);
    add_face(0x02, 0x12, 0x52, 0x42, true);
    add_face(0x22, 0x32, 0x72, 0x62);
    add_face(0x01, 0x41, 0x61, 0x21, true);
    add_face(0x11, 0x51, 0x71, 0x31);
    // four bevels for left face
    add_face(0x04, 0x14, 0x12, 0x02, true);
    add_face(0x14, 0x34, 0x31, 0x11, true);
    add_face(0x34, 0x24, 0x22, 0x32, true);
    add_face(0x24, 0x04, 0x01, 0x21, true);
    // four bevels for right face
    add_face(0x44, 0x54, 0x52, 0x42);
    add_face(0x54, 0x74, 0x71, 0x51);
    add_face(0x74, 0x64, 0x62, 0x72);
    add_face(0x64, 0x44, 0x41, 0x61);
    // four missing bevels
    add_face(0x01, 0x41, 0x42, 0x02);
    add_face(0x21, 0x61, 0x62, 0x22, true);
    add_face(0x11, 0x51, 0x52, 0x12, true);
    add_face(0x31, 0x71, 0x72, 0x32);
    // 8 remaining triangles
    add_face(0x01, 0x02, 0x04);
    add_face(0x11, 0x12, 0x14, true);
    add_face(0x21, 0x22, 0x24, true);
    add_face(0x31, 0x32, 0x34);
    add_face(0x41, 0x42, 0x44, true);
    add_face(0x51, 0x52, 0x54);
    add_face(0x61, 0x62, 0x64);
    add_face(0x71, 0x72, 0x74, true);
}

void BrickShape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void BrickShape::add_face(int v1, int v2, int v3, bool flip)
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

float3 BrickShape::decode_vertex(int v)
{
    float3 r;

    if (v & 0x40) {
        r.v1 = (v & 4) ? m_dimx / 2.0 : m_dimx / 2.0 - m_dimb;
    } else {
        r.v1 = (v & 4) ? -m_dimx / 2.0 : -m_dimx / 2.0 + m_dimb;
    }
    if (v & 0x20) {
        r.v2 = (v & 2) ? m_dimy / 2.0 : m_dimy / 2.0 - m_dimb;
    } else {
        r.v2 = (v & 2) ? -m_dimy / 2.0 : -m_dimy / 2.0 + m_dimb;
    }
    if (v & 0x10) {
        r.v3 = (v & 1) ? m_dimz / 2.0 : m_dimz / 2.0 - m_dimb;
    } else {
        r.v3 = (v & 1) ? -m_dimz / 2.0 : -m_dimz / 2.0 + m_dimb;
    }
    return r;
}

