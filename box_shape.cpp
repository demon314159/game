
#include "box_shape.h"
#include <cstddef>

BoxShape::BoxShape(Float3 pl0, Float3 pl1, Float3 pl2, Float3 pl3, Float3 pu0, Float3 pu1, Float3 pu2, Float3 pu3)
    : m_pl0(pl0)
    , m_pl1(pl1)
    , m_pl2(pl2)
    , m_pl3(pl3)
    , m_pu0(pu0)
    , m_pu1(pu1)
    , m_pu2(pu2)
    , m_pu3(pu3)
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

BoxShape::~BoxShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int BoxShape::facets() const
{
    return m_facet_count;
}

Facet BoxShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void BoxShape::define_shape()
{
    // faces
    add_face(m_pl0, m_pl1, m_pl2, m_pl3, true); // lower
    add_face(m_pu0, m_pu1, m_pu2, m_pu3);       // top
    add_face(m_pl1, m_pl2, m_pu2, m_pu1);       // back
    add_face(m_pl0, m_pl3, m_pu3, m_pu0, true); // front
    add_face(m_pl0, m_pl1, m_pu1, m_pu0);       // left
    add_face(m_pl2, m_pl3, m_pu3, m_pu2);       // right
}

void BoxShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void BoxShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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
