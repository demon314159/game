
#include "star_shape.h"
#include <math.h>
#include <cstddef>

StarShape::StarShape(int spikes, float width)
    : m_spikes(spikes)
    , m_width(width)
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

StarShape::~StarShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int StarShape::facets() const
{
    return m_facet_count;
}

Facet StarShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void StarShape::define_shape()
{
    float da = 2.0 * 3.1415926536 / (2.0 * (float) m_spikes);
    float dz = 0.01;
    float r1 = m_width / 2;
    float r0 = 0.76389 * r1 / 2.0;
    for (int i = 0; i < m_spikes; i++) {
        float main_angle = 2.0 * da * (float) i;
        float left_angle = main_angle + da;
        float right_angle = main_angle - da;
        Float3 v1 = {r1 * sin(main_angle), dz, r1 * cos(main_angle)};
        Float3 v2 = {r0 * sin(left_angle), dz, r0 * cos(left_angle)};
        Float3 v3 = {0.0, dz, 0.0};
        Float3 v4 = {r0 * sin(right_angle), dz, r0 * cos(right_angle)};
        add_face(v1, v2, v3, v4);
    }
}

void StarShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void StarShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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


