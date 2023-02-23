
#include "curved_section.h"
#include "curved_track_shape.h"
#include "track_style.h"
#include <cmath>

#define PI 3.1415926536

CurvedSection::CurvedSection(int lanes, double radius, double total_angle, double start_angle, Double3 start_anchor)
    : m_lanes(lanes)
    , m_radius(radius)
    , m_total_angle(total_angle)
    , m_start_angle(start_angle)
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

double CurvedSection::start_angle() const
{
    return m_start_angle;
}

Double3 CurvedSection::start_anchor() const
{
    return m_start_anchor;
}

double CurvedSection::end_angle() const
{
    return m_end_angle;
}

Double3 CurvedSection::end_anchor() const
{
    return m_end_anchor;
}

CadModel CurvedSection::cad_model() const
{
    CadModel cm;
    CadModel s = CadModel(CurvedTrackShape(m_lanes, m_radius, m_total_angle));
    s.rotate_ay(m_start_angle);
    cm.add(s, m_start_anchor.v1, m_start_anchor.v2, m_start_anchor.v3);
    return cm;
}
