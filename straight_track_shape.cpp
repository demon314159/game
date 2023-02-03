
#include "straight_track_shape.h"
#include "track_style.h"
#include <cstddef>

StraightTrackShape::StraightTrackShape(int lanes, float length)
    : m_lanes(lanes)
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

StraightTrackShape::~StraightTrackShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int StraightTrackShape::facets() const
{
    return m_facet_count;
}

Facet StraightTrackShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void StraightTrackShape::define_shape()
{
    float dy = TrackStyle::track_height;
    float z0 = 0.0;
    float z1 = -m_length;
    float db = TrackStyle::track_bevel;
    float sh = TrackStyle::slot_height;
    Float3 tp = TrackStyle::track_paint().ambient_color();
    Float3 sp = TrackStyle::slot_paint().ambient_color();
    Float3 rp = TrackStyle::rail_paint().ambient_color();

    float dimx = 2.0 * TrackStyle::car_shoulder
               + (float) m_lanes * TrackStyle::car_width
               + (float) (m_lanes - 1) * TrackStyle::car_gap;

    float x0 = -dimx / 2.0;
    float x1 = x0 + TrackStyle::track_bevel;
    float x2 = x0 + TrackStyle::car_shoulder + TrackStyle::car_width / 2.0
             - TrackStyle::slot_width / 2.0 - TrackStyle::rail_width;
    float x3 = x2 + TrackStyle::rail_width;
    float x4 = x3 + TrackStyle::slot_width;
    float x5 = x4 + TrackStyle::rail_width;

    add_face(0.0, tp, {x0, -dy, z0}, {x0, -dy, z1}, {x0, dy - db, z1}, {x0, dy - db, z0}, true);
    add_face(0.0, tp, {x0, dy - db, z0}, {x0, dy - db, z1}, {x1, dy, z1}, {x1, dy, z0}, true);
    add_face(0.0, tp, {x1, dy, z0}, {x1, dy, z1}, {x2, dy, z1}, {x2, dy, z0}, true);
    add_face(1.0, rp, {x2, dy, z0}, {x2, dy, z1}, {x3, dy, z1}, {x3, dy, z0}, true);
    add_face(0.0, tp, {x3, dy, z0}, {x3, dy, z1}, {x3, dy - sh, z1}, {x3, dy - sh, z0}, true);
    add_face(1.0, sp, {x3, dy - sh, z0}, {x3, dy - sh, z1}, {x4, dy - sh, z1}, {x4, dy - sh, z0}, true);
    add_face(0.0, tp, {x4, dy - sh, z0}, {x4, dy - sh, z1}, {x4, dy, z1}, {x4, dy, z0}, true);
    add_face(1.0, rp, {x4, dy, z0}, {x4, dy, z1}, {x5, dy, z1}, {x5, dy, z0}, true);
    for (int i = 1; i < m_lanes; i++) {
        x1 = x5;
        x2 = x2 + TrackStyle::car_gap + TrackStyle::car_width;
        x3 = x3 + TrackStyle::car_gap + TrackStyle::car_width;
        x4 = x4 + TrackStyle::car_gap + TrackStyle::car_width;
        x5 = x5 + TrackStyle::car_gap + TrackStyle::car_width;
        add_face(0.0, tp, {x1, dy, z0}, {x1, dy, z1}, {x2, dy, z1}, {x2, dy, z0}, true);
        add_face(1.0, rp, {x2, dy, z0}, {x2, dy, z1}, {x3, dy, z1}, {x3, dy, z0}, true);
        add_face(0.0, tp, {x3, dy, z0}, {x3, dy, z1}, {x3, dy - sh, z1}, {x3, dy - sh, z0}, true);
        add_face(1.0, sp, {x3, dy - sh, z0}, {x3, dy - sh, z1}, {x4, dy - sh, z1}, {x4, dy - sh, z0}, true);
        add_face(0.0, tp, {x4, dy - sh, z0}, {x4, dy - sh, z1}, {x4, dy, z1}, {x4, dy, z0}, true);
        add_face(1.0, rp, {x4, dy, z0}, {x4, dy, z1}, {x5, dy, z1}, {x5, dy, z0}, true);
    }
    float x6 = dimx / 2.0 - TrackStyle::track_bevel;
    float x7 = dimx / 2.0;
    add_face(0.0, tp, {x5, dy, z0}, {x5, dy, z1}, {x6, dy, z1}, {x6, dy, z0}, true);
    add_face(0.0, tp, {x6, dy, z0}, {x6, dy, z1}, {x7, dy - db, z1}, {x7, dy - db, z0}, true);
    add_face(0.0, tp, {x7, dy - db, z0}, {x7, dy - db, z1}, {x7, -dy, z1}, {x7, -dy, z0}, true);
}

void StraightTrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(animation_id, color, v1, v2, v3, flip);
    add_face(animation_id, color, v1, v3, v4, flip);
}

void StraightTrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip)
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


