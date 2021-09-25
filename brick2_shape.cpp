
#include "brick2_shape.h"
#include <stdio.h>

Brick2Shape::Brick2Shape(float dimx, float dimy, float dimz, float dimb)
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

Brick2Shape::~Brick2Shape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int Brick2Shape::facets() const
{
    return m_facet_count;
}

facet Brick2Shape::get_facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void Brick2Shape::define_shape()
{
    // faces
    add_face(0x06, 0x16, 0x36, 0x26);
    add_face(0x46, 0x56, 0x76, 0x66, true);
    add_face(0x06, 0x16, 0x56, 0x46, true);
    add_face(0x26, 0x36, 0x76, 0x66);
    add_face(0x01, 0x41, 0x61, 0x21, true);
    add_face(0x11, 0x51, 0x71, 0x31);
    // four bevels for front face
    add_face(0x16, 0x36, 0x31, 0x11, true);
    add_face(0x56, 0x76, 0x71, 0x51);
    add_face(0x31, 0x71, 0x76, 0x36);
    add_face(0x11, 0x51, 0x56, 0x16, true);

    // four bevels for back face
    //
    add_face(0x26, 0x06, 0x01, 0x21, true);
    add_face(0x66, 0x46, 0x41, 0x61);
    add_face(0x21, 0x61, 0x66, 0x26, true);
    add_face(0x01, 0x41, 0x46, 0x06);
}

void Brick2Shape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    printf("add_face(%d, %d, %d, %d, %s)\n", v1, v2, v3, v4, flip ? "true" : "false");
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void Brick2Shape::add_face(int v1, int v2, int v3, bool flip)
{
    printf("add_face(%d, %d, %d, %s)\n", v1, v2, v3, flip ? "true" : "false");
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

float3 Brick2Shape::decode_vertex(int v)
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

