
#include "car_shape.h"
#include "radial.h"
#include "curve.h"
#include "track_style.h"
#include <cstddef>

#include "stdio.h"

CarShape::CarShape(float width, float length)
    : m_width(width)
    , m_length(length)
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

CarShape::~CarShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CarShape::facets() const
{
    return m_facet_count;
}

Facet CarShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CarShape::define_shape()
{
    int np = 4;
    Matrix given(np, 2);
    given.set(0, 0, 0.0); given.set(0, 1, 5.0);
    given.set(1, 0, 10.0); given.set(1, 1, 4.0);
    given.set(2, 0, 9.0); given.set(2, 1, 0.5);
    given.set(3, 0, 0.0); given.set(3, 1, 0.0);
    int top_steps = 9;
    int bottom_steps = 9;
    int side_steps = 9;
    int fillet_steps = 9;
    double top_shrink = 0.05;
    double bottom_shrink = 0.05;
    double side_top_shrink = 0.2;
    double side_bottom_shrink = 0.2;
    // Find top radial
    Double2 p1 = {-given.get(1, 0), given.get(1, 1)};
    Double2 p2 = {given.get(0, 0), given.get(0, 1)};
    Double2 p3 = {given.get(1, 0), given.get(1, 1)};
    Radial top_rad(p1, p2, p3, top_steps);
    p1 = {given.get(2, 0), given.get(2, 1)};
    p2 = {given.get(3, 0), given.get(3, 1)};
    p3 = {-given.get(2, 0), given.get(2, 1)};
    Radial bottom_rad(p1, p2, p3, bottom_steps);
    p1 = {given.get(1, 0), given.get(1, 1)};
    p2 = {given.get(2, 0), given.get(2, 1)};
    Radial right_rad(p1, p2, 10.0, side_steps);
    p2 = {-given.get(1, 0), given.get(1, 1)};
    p1 = {-given.get(2, 0), given.get(2, 1)};
    Radial left_rad(p1, p2, 10.0, side_steps);
    top_rad = top_rad.shrunk(top_shrink, 1.0 - top_shrink);
    bottom_rad = bottom_rad.shrunk(bottom_shrink, 1.0 - bottom_shrink);
    right_rad = right_rad.shrunk(side_top_shrink, 1.0 - side_bottom_shrink);
    Radial top_right_rad(top_rad, right_rad, fillet_steps);
    Radial top_left_rad(left_rad, top_rad, fillet_steps);
    Radial bottom_right_rad(right_rad, bottom_rad, fillet_steps);
    Radial bottom_left_rad(bottom_rad, left_rad, fillet_steps);
    Curve curve;
//    curve.add(bottom_left_rad);
    curve.add(left_rad);
    curve.add(top_left_rad);
//    curve.add(top_rad);
//    curve.add(top_right_rad);
//    curve.add(right_rad);
//    curve.add(bottom_right_rad);
//    curve.add(bottom_rad);

    float z0 = 0.0;
    float z1 = 5.0;
    Float3 cp = TrackStyle::slot_paint().ambient_color();
    for (int i = 1; i < curve.steps(); i++) {
        float x0 = curve.x(i - 1);
        float y0 = curve.y(i - 1);
        float x1 = curve.x(i);
        float y1 = curve.y(i);
        add_face(0.0, cp, {x0, y0, z0}, {x0, y0, z1}, {x1, y1, z1}, {x1, y1, z0}, true);
    }
}

void CarShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(animation_id, color, v1, v2, v3, flip);
    add_face(animation_id, color, v1, v3, v4, flip);
}

void CarShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip)
{
    if (!m_count_mode) {
        m_facet[m_facet_count].animation_id = animation_id;
        m_facet[m_facet_count].color = color;
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


