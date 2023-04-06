
#include "curved_left_track_shape.h"
#include "track_style.h"
#include "rise_profile.h"
#include "pi.h"
#include "math.h"
#include <cstddef>

CurvedLeftTrackShape::CurvedLeftTrackShape(int lanes, float radius, float total_angle, float rise)
    : m_lanes(lanes)
    , m_rise(rise)
    , m_radius(radius)
    , m_total_angle(total_angle)
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

CurvedLeftTrackShape::~CurvedLeftTrackShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int CurvedLeftTrackShape::facets() const
{
    return m_facet_count;
}

Facet CurvedLeftTrackShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void CurvedLeftTrackShape::define_shape()
{
    float dy = TrackStyle::track_height;
    float db = TrackStyle::track_bevel;
    float sh = TrackStyle::slot_height;
    Float3 tp = TrackStyle::track_paint().ambient_color();
    Float3 sp = TrackStyle::slot_paint().ambient_color();
    Float3 rp = TrackStyle::rail_paint().ambient_color();

    float dimx = 2.0 * TrackStyle::car_shoulder
               + (float) m_lanes * TrackStyle::car_width
               + (float) (m_lanes - 1) * TrackStyle::car_gap;

    float approx_dangle = 2.0; // degrees
    int steps = round(m_total_angle / approx_dangle);
    float dangle = m_total_angle / (float) steps;
    RiseProfile pro(m_rise);
    for (int j = 0; j < steps; j++) {
        float angle = dangle * (float) j;

        float x0 = -dimx / 2.0;
        float x1 = x0 + TrackStyle::track_bevel;
        float x2 = x0 + TrackStyle::car_shoulder + TrackStyle::car_width / 2.0
             - TrackStyle::slot_width / 2.0 - TrackStyle::rail_width;
        float x3 = x2 + TrackStyle::rail_width;
        float x4 = x3 + TrackStyle::slot_width;
        float x5 = x4 + TrackStyle::rail_width;

        float cosa = cos(angle * PI / 180.0);
        float cosb = cos((angle + dangle) * PI / 180.0);
        float sina = sin(angle * PI / 180.0);
        float sinb = sin((angle + dangle) * PI / 180.0);

        float xa0 = -m_radius + (x0 + m_radius) * cosa;
        float xb0 = -m_radius + (x0 + m_radius) * cosb;
        float za0 = - (x0 + m_radius) * sina;
        float zb0 = - (x0 + m_radius) * sinb;

        float xa1 = -m_radius + (x1 + m_radius) * cosa;
        float xb1 = -m_radius + (x1 + m_radius) * cosb;
        float za1 = - (x1 + m_radius) * sina;
        float zb1 = - (x1 + m_radius) * sinb;

        float xa2 = -m_radius + (x2 + m_radius) * cosa;
        float xb2 = -m_radius + (x2 + m_radius) * cosb;
        float za2 = - (x2 + m_radius) * sina;
        float zb2 = - (x2 + m_radius) * sinb;

        float xa3 = -m_radius + (x3 + m_radius) * cosa;
        float xb3 = -m_radius + (x3 + m_radius) * cosb;
        float za3 = - (x3 + m_radius) * sina;
        float zb3 = - (x3 + m_radius) * sinb;

        float xa4 = -m_radius + (x4 + m_radius) * cosa;
        float xb4 = -m_radius + (x4 + m_radius) * cosb;
        float za4 = - (x4 + m_radius) * sina;
        float zb4 = - (x4 + m_radius) * sinb;

        float xa5 = -m_radius + (x5 + m_radius) * cosa;
        float xb5 = -m_radius + (x5 + m_radius) * cosb;
        float za5 = - (x5 + m_radius) * sina;
        float zb5 = - (x5 + m_radius) * sinb;

        float ya = pro.height((float) j, (float) steps);
        float yb = pro.height((float) j + 1, (float) steps);
        add_face(0.0, tp, {xa0, -dy + ya, za0},     {xb0, -dy + yb, zb0},     {xb0, dy - db + yb, zb0}, {xa0, dy - db + ya, za0}, true);
        add_face(0.0, tp, {xa0, dy - db + ya, za0}, {xb0, dy - db + yb, zb0}, {xb1, dy + yb, zb1},      {xa1, dy + ya, za1}, true);
        add_face(0.0, tp, {xa1, dy + ya, za1},      {xb1, dy + yb, zb1},      {xb2, dy + yb, zb2},      {xa2, dy + ya, za2}, true);
        add_face(1.0, rp, {xa2, dy + ya, za2},      {xb2, dy + yb, zb2},      {xb3, dy + yb, zb3},      {xa3, dy + ya, za3}, true);
        add_face(0.0, tp, {xa3, dy + ya, za3},      {xb3, dy + yb, zb3},      {xb3, dy - sh + yb, zb3}, {xa3, dy - sh + ya, za3}, true);
        add_face(1.0, sp, {xa3, dy - sh + ya, za3}, {xb3, dy - sh + yb, zb3}, {xb4, dy - sh + yb, zb4}, {xa4, dy - sh + ya, za4}, true);
        add_face(0.0, tp, {xa4, dy - sh + ya, za4}, {xb4, dy - sh + yb, zb4}, {xb4, dy + yb, zb4},      {xa4, dy + ya, za4}, true);
        add_face(1.0, rp, {xa4, dy + ya, za4},      {xb4, dy + yb, zb4},      {xb5, dy + yb, zb5},      {xa5, dy + ya, za5}, true);

        for (int i = 1; i < m_lanes; i++) {
            x1 = x5;
            x2 = x2 + TrackStyle::car_gap + TrackStyle::car_width;
            x3 = x3 + TrackStyle::car_gap + TrackStyle::car_width;
            x4 = x4 + TrackStyle::car_gap + TrackStyle::car_width;
            x5 = x5 + TrackStyle::car_gap + TrackStyle::car_width;

            xa1 = -m_radius + (x1 + m_radius) * cosa;
            xb1 = -m_radius + (x1 + m_radius) * cosb;
            za1 = - (x1 + m_radius) * sina;
            zb1 = - (x1 + m_radius) * sinb;

            xa2 = -m_radius + (x2 + m_radius) * cosa;
            xb2 = -m_radius + (x2 + m_radius) * cosb;
            za2 = - (x2 + m_radius) * sina;
            zb2 = - (x2 + m_radius) * sinb;

            xa3 = -m_radius + (x3 + m_radius) * cosa;
            xb3 = -m_radius + (x3 + m_radius) * cosb;
            za3 = - (x3 + m_radius) * sina;
            zb3 = - (x3 + m_radius) * sinb;

            xa4 = -m_radius + (x4 + m_radius) * cosa;
            xb4 = -m_radius + (x4 + m_radius) * cosb;
            za4 = - (x4 + m_radius) * sina;
            zb4 = - (x4 + m_radius) * sinb;

            xa5 = -m_radius + (x5 + m_radius) * cosa;
            xb5 = -m_radius + (x5 + m_radius) * cosb;
            za5 = - (x5 + m_radius) * sina;
            zb5 = - (x5 + m_radius) * sinb;

            add_face(0.0, tp, {xa1, dy + ya, za1}, {xb1, dy + yb, zb1}, {xb2, dy + yb, zb2}, {xa2, dy + ya, za2}, true);
            add_face(1.0, rp, {xa2, dy + ya, za2}, {xb2, dy + yb, zb2}, {xb3, dy + yb, zb3}, {xa3, dy + ya, za3}, true);
            add_face(0.0, tp, {xa3, dy + ya, za3}, {xb3, dy + yb, zb3}, {xb3, dy - sh + yb, zb3}, {xa3, dy - sh + ya, za3}, true);
            add_face(1.0, sp, {xa3, dy - sh + ya, za3}, {xb3, dy - sh + yb, zb3}, {xb4, dy - sh + yb, zb4}, {xa4, dy - sh + ya, za4}, true);
            add_face(0.0, tp, {xa4, dy - sh + ya, za4}, {xb4, dy - sh + yb, zb4}, {xb4, dy + yb, zb4}, {xa4, dy + ya, za4}, true);
            add_face(1.0, rp, {xa4, dy + ya, za4}, {xb4, dy + yb, zb4}, {xb5, dy + yb, zb5}, {xa5, dy + ya, za5}, true);
        }
        float x6 = dimx / 2.0 - TrackStyle::track_bevel;
        float x7 = dimx / 2.0;

        float xa6 = -m_radius + (x6 + m_radius) * cosa;
        float xb6 = -m_radius + (x6 + m_radius) * cosb;
        float za6 = - (x6 + m_radius) * sina;
        float zb6 = - (x6 + m_radius) * sinb;

        float xa7 = -m_radius + (x7 + m_radius) * cosa;
        float xb7 = -m_radius + (x7 + m_radius) * cosb;
        float za7 = - (x7 + m_radius) * sina;
        float zb7 = - (x7 + m_radius) * sinb;

        add_face(0.0, tp, {xa5, dy + ya, za5}, {xb5, dy + yb, zb5}, {xb6, dy + yb, zb6}, {xa6, dy + ya, za6}, true);
        add_face(0.0, tp, {xa6, dy + ya, za6}, {xb6, dy + yb, zb6}, {xb7, dy - db + yb, zb7}, {xa7, dy - db + yb, za7}, true);
        add_face(0.0, tp, {xa7, dy - db + ya, za7}, {xb7, dy - db + yb, zb7}, {xb7, -dy + yb, zb7}, {xa7, -dy + ya, za7}, true);
    }
}

void CurvedLeftTrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(animation_id, color, v1, v2, v3, flip);
    add_face(animation_id, color, v1, v3, v4, flip);
}

void CurvedLeftTrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip)
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


