
#include "straight_section.h"
#include <cmath>

#define PI 3.1415926536

StraightSection::StraightSection(int lanes, double length, double angle, Double3 anchor)
    : m_lanes(lanes)
    , m_length(length)
    , m_angle(angle)
    , m_anchor(anchor)
{
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
    return m_angle;
}

Double3 StraightSection::position(int lane, double distance) const
{
    double sina = sin(m_angle * PI / 180.0);
    double cosa = cos(m_angle * PI / 180.0);
    return {m_anchor.v1 - distance * sina, m_anchor.v2, m_anchor.v3 - distance * cosa};
}

