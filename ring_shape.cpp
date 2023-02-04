
#include "ring_shape.h"
#include "math.h"

RingShape::RingShape(float radius_o, float radius_i, float height, float upper_bevel_o, float upper_bevel_i, float lower_bevel_o, float lower_bevel_i)
    : m_radius_o(radius_o)
    , m_radius_i(radius_i)
    , m_height(height)
    , m_upper_bevel_o(upper_bevel_o)
    , m_upper_bevel_i(upper_bevel_i)
    , m_lower_bevel_o(lower_bevel_o)
    , m_lower_bevel_i(lower_bevel_i)
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

RingShape::~RingShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int RingShape::facets() const
{
    return m_facet_count;
}

Facet RingShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void RingShape::define_shape()
{
    float approx_dangle = 2.0; // degrees
    int steps = round(360.0 / approx_dangle);
    float dangle = 360.0 / (float) steps;
    float dy = m_height / 2.0;
    float ub_o = m_upper_bevel_o;
    float ub_i = m_upper_bevel_i;
    float lb_o = m_lower_bevel_o;
    float lb_i = m_lower_bevel_i;
    for (int j = 0; j < steps; j++) {
        float angle = dangle * (float) j;
        float cosa = cos(angle * 3.1415926535 / 180.0);
        float cosb = cos((angle + dangle) * 3.1415926535 / 180.0);
        float sina = sin(angle * 3.1415926535 / 180.0);
        float sinb = sin((angle + dangle) * 3.1415926535 / 180.0);
        float xa0 = m_radius_i * cosa;
        float xb0 = m_radius_i * cosb;
        float za0 = m_radius_i * sina;
        float zb0 = m_radius_i * sinb;
        float xa1 = (m_radius_i + lb_i) * cosa;
        float xb1 = (m_radius_i + lb_i) * cosb;
        float za1 = (m_radius_i + lb_i) * sina;
        float zb1 = (m_radius_i + lb_i) * sinb;
        float xa2 = (m_radius_o - lb_o) * cosa;
        float xb2 = (m_radius_o - lb_o) * cosb;
        float za2 = (m_radius_o - lb_o) * sina;
        float zb2 = (m_radius_o - lb_o) * sinb;
        float xa3 = m_radius_o * cosa;
        float xb3 = m_radius_o * cosb;
        float za3 = m_radius_o * sina;
        float zb3 = m_radius_o * sinb;
        float xa4 = (m_radius_o - ub_o) * cosa;
        float xb4 = (m_radius_o - ub_o) * cosb;
        float za4 = (m_radius_o - ub_o) * sina;
        float zb4 = (m_radius_o - ub_o) * sinb;
        float xa5 = (m_radius_i + ub_i) * cosa;
        float xb5 = (m_radius_i + ub_i) * cosb;
        float za5 = (m_radius_i + ub_i) * sina;
        float zb5 = (m_radius_i + ub_i) * sinb;
        add_face({xa0, -dy + lb_i, za0}, {xb0, -dy + lb_i, zb0}, {xb0, dy - ub_i, zb0}, {xa0, dy - ub_i, za0}, false);
        add_face({xa3, -dy + lb_o, za3}, {xb3, -dy + lb_o, zb3}, {xb3, dy - ub_o, zb3}, {xa3, dy - ub_o, za3}, true);

        add_face({xa1, -dy, za1}, {xa2, -dy, za2}, {xb2, -dy, zb2}, {xb1, -dy, zb1}, false);
        if (lb_i != 0.0)
            add_face({xa0, -dy + lb_i, za0}, {xa1, -dy, za1}, {xb1, -dy, zb1}, {xb0, -dy + lb_i, zb0}, false);
        if (lb_o != 0.0)
            add_face({xa2, -dy, za2}, {xa3, -dy + lb_o, za3}, {xb3, -dy + lb_o, zb3}, {xb2, -dy, zb2}, false);

        add_face({xa5, dy, za5}, {xa4, dy, za4}, {xb4, dy, zb4}, {xb5, dy, zb5}, true);
        if (ub_i != 0.0)
            add_face({xa0, dy - ub_i, za0}, {xa5, dy, za5}, {xb5, dy, zb5}, {xb0, dy - ub_i, zb0}, true);
        if (ub_o != 0.0)
            add_face({xa4, dy, za4}, {xa3, dy - ub_o, za3}, {xb3, dy - ub_o, zb3}, {xb4, dy, zb4}, true);
    }
}

void RingShape::add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(v1, v2, v3, flip);
    add_face(v1, v3, v4, flip);
}

void RingShape::add_face(Float3 v1, Float3 v2, Float3 v3, bool flip)
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

