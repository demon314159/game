
#include "gable_brick_shape.h"
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <cstddef>

GableBrickShape::GableBrickShape(float dimx, float dimy, float dimz, float dimb, int orientation)
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
        if (orientation == 3)
            rotate_ay(90.0);
        if (orientation == 0)
            rotate_ay(180.0);
        if (orientation == 1)
            rotate_ay(270.0);
    }
}

GableBrickShape::~GableBrickShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int GableBrickShape::facets() const
{
    return m_facet_count;
}

Facet GableBrickShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void GableBrickShape::define_shape()
{
    // faces
    add_face(0x44, 0x54, 0x74, 0x64, true);
    add_face(0x02, 0x12, 0x52, 0x42, true);
    add_face(0x04, 0x14, 0x72, 0x62);
    add_face(0x01, 0x41, 0x61, true);
    add_face(0x11, 0x51, 0x71);

    // one bevel for left face
    add_face(0x04, 0x14, 0x12, 0x02, true);

    // four bevels for right face
    add_face(0x44, 0x54, 0x52, 0x42);
    add_face(0x54, 0x74, 0x71, 0x51);
    add_face(0x74, 0x64, 0x62, 0x72);
    add_face(0x64, 0x44, 0x41, 0x61);
    // four missing bevels
    add_face(0x01, 0x41, 0x42, 0x02);
    add_face(0x01, 0x61, 0x62, 0x04, true);
    add_face(0x11, 0x51, 0x52, 0x12, true);
    add_face(0x11, 0x71, 0x72, 0x14);

    // 6 remaining triangles
    add_face(0x01, 0x02, 0x04);
    add_face(0x11, 0x12, 0x14, true);
    add_face(0x41, 0x42, 0x44, true);
    add_face(0x51, 0x52, 0x54);
    add_face(0x61, 0x62, 0x64);
    add_face(0x71, 0x72, 0x74, true);
}

void GableBrickShape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void GableBrickShape::add_face(int v1, int v2, int v3, bool flip)
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

Float3 GableBrickShape::decode_vertex(int v)
{
    Float3 r;

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

void GableBrickShape::rotate_vertex(Float3& vertex, const QMatrix4x4& matrix)
{
    QVector4D r = matrix * QVector4D(vertex.v1, vertex.v2, vertex.v3, 1.0);
    vertex.v1 = r.x();
    vertex.v2 = r.y();
    vertex.v3 = r.z();
}

void GableBrickShape::rotate_ay(float angle)
{
    QVector3D my_axis = {0.0, 1.0, 0.0};
    QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, angle);
    QMatrix4x4 matrix;
    matrix.rotate(my_rot);
    for (int i = 0; i < m_facet_count; i++) {
        rotate_vertex(m_facet[i].v1, matrix);
        rotate_vertex(m_facet[i].v2, matrix);
        rotate_vertex(m_facet[i].v3, matrix);
    }
}





