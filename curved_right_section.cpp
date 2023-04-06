
#include "curved_right_section.h"
#include "curved_right_track_shape.h"
#include "track_style.h"
#include "pi.h"
#include <cmath>

CurvedRightSection::CurvedRightSection(int lanes, double radius, double total_angle, Anchor start_anchor)
    : m_lanes(lanes)
    , m_radius(radius)
    , m_total_angle(total_angle)
    , m_start_anchor(start_anchor)
{
    double sina = sin(total_angle * PI / 180.0);
    double cosa = cos(total_angle * PI / 180.0);
    double end_x = m_radius - m_radius * cosa;
    double end_z = -m_radius * sina;
    sina = sin(start_anchor.a * PI / 180.0);
    cosa = cos(start_anchor.a * PI / 180.0);
    m_end_anchor.x = m_start_anchor.x + end_x * cosa + end_z * sina;
    m_end_anchor.y = m_start_anchor.y;
    m_end_anchor.z = m_start_anchor.z - end_x * sina + end_z * cosa;
    m_end_anchor.a = m_start_anchor.a - total_angle;
}

CurvedRightSection::~CurvedRightSection()
{
}

double CurvedRightSection::rlane(int lane) const
{
    double dimx = 2.0 * TrackStyle::car_shoulder
               + (float) m_lanes * TrackStyle::car_width
               + (float) (m_lanes - 1) * TrackStyle::car_gap;
    double x0 = -dimx / 2.0;
    double x2 = x0 + TrackStyle::car_shoulder + TrackStyle::car_width / 2.0;
    double xc = x2 + ((double) lane) * (TrackStyle::car_width + TrackStyle::car_gap);
    return m_radius - xc;
}

double CurvedRightSection::total_distance(int lane) const
{
    return rlane(lane) * m_total_angle * PI / 180.0;
}

double CurvedRightSection::car_yaw(int lane, double distance) const
{
    return m_start_anchor.a - (distance / rlane(lane)) * 180.0 / PI;
}

Double3 CurvedRightSection::car_position(int lane, double distance) const
{
    double r = rlane(lane);
    double angle = distance / r;
    double sina = sin(angle);
    double cosa = cos(angle);
    double car_x = m_radius - r * cosa;
    double car_z = -r * sina;
    sina = sin(m_start_anchor.a * PI / 180.0);
    cosa = cos(m_start_anchor.a * PI / 180.0);
    return {m_start_anchor.x + car_x * cosa + car_z * sina, m_start_anchor.y, m_start_anchor.z - car_x * sina + car_z * cosa};
}

Anchor CurvedRightSection::start_anchor() const
{
    return m_start_anchor;
}

Anchor CurvedRightSection::end_anchor() const
{
    return m_end_anchor;
}

CadModel CurvedRightSection::cad_model() const
{
    CadModel cm;
    CadModel s = CadModel(CurvedRightTrackShape(m_lanes, m_radius, m_total_angle));
    s.rotate_ay(m_start_anchor.a);
    cm.add(s, m_start_anchor.x, m_start_anchor.y, m_start_anchor.z);
    return cm;
}
