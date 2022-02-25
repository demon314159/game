
#include "mouse_vector_shape.h"
#include <cstddef>

MouseVectorShape::MouseVectorShape(const MouseVector& mv, float t0, float t1)
    : m_pt0({0.0, 0.0, 0.0})
    , m_pt1({0.0, 0.0, 0.0})
    , m_dimb(0.025)
    , m_count_mode(true)
    , m_facet_count(0)
    , m_facet(NULL)
{
    m_pt0.v1 = mv.origin().v1 + t0 * mv.vector().v1;
    m_pt0.v2 = mv.origin().v2 + t0 * mv.vector().v2;
    m_pt0.v3 = mv.origin().v3 + t0 * mv.vector().v3;
    m_pt1.v1 = mv.origin().v1 + t1 * mv.vector().v1;
    m_pt1.v2 = mv.origin().v2 + t1 * mv.vector().v2;
    m_pt1.v3 = mv.origin().v3 + t1 * mv.vector().v3;
    if (m_pt1.v3 > m_pt0.v3) {
        Float3 tp = m_pt0;
        m_pt0 = m_pt1;
        m_pt1 = tp;
    }
    define_shape();
    m_count_mode = false;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape();
    }
}

MouseVectorShape::~MouseVectorShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int MouseVectorShape::facets() const
{
    return m_facet_count;
}

Facet MouseVectorShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void MouseVectorShape::define_shape()
{
    // faces
    add_face(0, 1, 3, 2);
    add_face(4, 5, 7, 6, true);
    add_face(0, 1, 5, 4, true);
    add_face(2, 3, 7, 6);
    add_face(0, 4, 6, 2, true);
    add_face(1, 5, 7, 3);
}

void MouseVectorShape::add_face(int v1, int v2, int v3, int v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void MouseVectorShape::add_face(int v1, int v2, int v3, bool flip)
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

Float3 MouseVectorShape::decode_vertex(int v)
{
    Float3 r;
    Float3 tp = v & 4 ? m_pt1 : m_pt0;
    r.v1 = v & 2 ? tp.v1 + m_dimb : tp.v1 - m_dimb;
    r.v2 = v & 1 ? tp.v2 + m_dimb : tp.v2 - m_dimb;
    r.v3 = tp.v3;
    return r;
}

