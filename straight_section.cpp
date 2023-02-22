
#include "straight_section.h"
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
    return m_length;
}

double StraightSection::angle(int lane, double distance) const
{
    return m_start_angle;
}

Double3 StraightSection::position(int lane, double distance) const
{
    double sina = sin(m_start_angle * PI / 180.0);
    double cosa = cos(m_start_angle * PI / 180.0);
    return {m_start_anchor.v1 - distance * sina, m_start_anchor.v2, m_start_anchor.v3 - distance * cosa};
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

