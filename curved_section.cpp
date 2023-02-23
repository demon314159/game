
#include "curved_section.h"
#include "curved_track_shape.h"
#include "track_style.h"
#include <cmath>

#define PI 3.1415926536

CurvedSection::CurvedSection(int lanes, double radius, double total_angle, Anchor start_anchor)
    : m_lanes(lanes)
    , m_radius(radius)
    , m_total_angle(total_angle)
    , m_start_anchor(start_anchor)
{
}

CurvedSection::~CurvedSection()
{
}

double CurvedSection::total_distance(int lane) const
{
}

double CurvedSection::car_angle(int lane, double distance) const
{
}

Double3 CurvedSection::car_position(int lane, double distance) const
{
}

Anchor CurvedSection::start_anchor() const
{
    return m_start_anchor;
}

Anchor CurvedSection::end_anchor() const
{
    return m_end_anchor;
}

CadModel CurvedSection::cad_model() const
{
    CadModel cm;
    CadModel s = CadModel(CurvedTrackShape(m_lanes, m_radius, m_total_angle));
    s.rotate_ay(m_start_anchor.a);
    cm.add(s, m_start_anchor.x, m_start_anchor.y, m_start_anchor.z);
    return cm;
}
