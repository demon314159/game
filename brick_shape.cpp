
#include "brick_shape.h"
#include <stdio.h>

BrickShape::BrickShape(float dimx, float dimy, float dimz, float dimb)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
    , m_facet_count(0)
    , m_count_mode(true)
{
    define_shape();
    m_count_mode = false;
}

BrickShape::~BrickShape()
{
}

int BrickShape::facet_count() const
{
    return m_facet_count;
}

void BrickShape::define_shape()
{
    add_face(0x01, 0x02, 0x04);
    add_face(0x01, 0x02, 0x04, true);
    add_face(0x22, 0x32, 0x72, 0x62);
    add_face(0x22, 0x32, 0x72, 0x62, true);
}

void BrickShape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    printf("add_face(%d, %d, %d, %d, %s)\n", v1, v2, v3, v4, flip ? "true" : "false");
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void BrickShape::add_face(int v1, int v2, int v3, bool flip)
{
    printf("add_face(%d, %d, %d, %s)\n", v1, v2, v3, flip ? "true" : "false");
    if (m_count_mode) {
        ++m_facet_count;
    } else {
        if (flip) {
            add_vertex(v1);
            add_vertex(v3);
            add_vertex(v2);
        } else {
            add_vertex(v1);
            add_vertex(v2);
            add_vertex(v3);
        }
    }
}

void BrickShape::add_vertex(int v)
{
    float x, y, z;
    printf("add_vertex(%d)\n", v);
    if (v & 0x40) {
        x = (v & 4) ? m_dimx / 2.0 : m_dimx / 2.0 - m_dimb;
    } else {
        x = (v & 4) ? -m_dimx / 2.0 : -m_dimx / 2.0 + m_dimb;
    }
    if (v & 0x20) {
        y = (v & 2) ? m_dimy / 2.0 : m_dimy / 2.0 - m_dimb;
    } else {
        y = (v & 2) ? -m_dimy / 2.0 : -m_dimy / 2.0 + m_dimb;
    }
    if (v & 0x10) {
        z = (v & 1) ? m_dimz / 2.0 : m_dimz / 2.0 - m_dimb;
    } else {
        z = (v & 1) ? -m_dimz / 2.0 : -m_dimz / 2.0 + m_dimb;
    }
    printf("  vertex(%8.3lf, %8.3lf, %8.3lf)\n", x, y, z);
}

