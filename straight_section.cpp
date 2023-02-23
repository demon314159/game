
#include "straight_section.h"
#include "straight_track_shape.h"
#include "track_style.h"
#include <cmath>

#define PI 3.1415926536

StraightSection::StraightSection(int lanes, double length, double start_angle, Double3 start_anchor)
    : m_lanes(lanes)
    , m_length(length)
    , m_start_angle(start_angle)
    , m_start_anchor(start_anchor)
{
    double sina = sin(start_angle * PI / 180.0);
    double cosa = cos(start_angle * PI / 180.0);
    m_end_angle = start_angle;
    m_end_anchor = {m_start_anchor.v1 - length * sina, m_start_anchor.v2, m_start_anchor.v3 - length * cosa};
}

StraightSection::~StraightSection()
{
}

double StraightSection::total_distance(int lane) const
{
    (void) lane;
    return m_length;
}

double StraightSection::car_angle(int lane, double distance) const
{
    (void) lane;
    (void) distance;
    return m_start_angle;
}

Double3 StraightSection::car_position(int lane, double distance) const
{
    double sina = sin(m_start_angle * PI / 180.0);
    double cosa = cos(m_start_angle * PI / 180.0);

    double dimx = 2.0 * TrackStyle::car_shoulder
               + (float) m_lanes * TrackStyle::car_width
               + (float) (m_lanes - 1) * TrackStyle::car_gap;

    double x0 = -dimx / 2.0;
    double x2 = x0 + TrackStyle::car_shoulder + TrackStyle::car_width / 2.0;
    double xc = x2 + ((double) lane) * (TrackStyle::car_width + TrackStyle::car_gap);
    double zc = - distance;
    double rot_xc = cosa * xc + sina * zc;
    double rot_zc = -sina * xc + cosa * zc;

    return {m_start_anchor.v1 + rot_xc, m_start_anchor.v2, m_start_anchor.v3 + rot_zc};
}

double StraightSection::start_angle() const
{
    return m_start_angle;
}

Double3 StraightSection::start_anchor() const
{
    return m_start_anchor;
}

double StraightSection::end_angle() const
{
    return m_end_angle;
}

Double3 StraightSection::end_anchor() const
{
    return m_end_anchor;
}

CadModel StraightSection::cad_model() const
{
    CadModel cm;
    CadModel s = CadModel(StraightTrackShape(m_lanes, m_length));
    s.rotate_ay(m_start_angle);
    cm.add(s, m_start_anchor.v1, m_start_anchor.v2, m_start_anchor.v3);
    return cm;
}
