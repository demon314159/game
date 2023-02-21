#include <cmath>
#include "car.h"

#include "stdio.h"

Car::Car()
    : m_speed(5.0)
    , m_section(0)
    , m_lane(0)
    , m_distance(0.0)
    , m_angle(0.0)
    , m_position({0.0, 0.0, 0.0})
{
}

Car::~Car()
{
}

void Car::advance(int nanoseconds, Section** section, int sections)
{
    float turns_per_second = 5.0 / 20.0;
    m_angle += ((360.0 * turns_per_second / 1000000000.0) * (double) nanoseconds);
//
// Just handle positive speed for now
//
    m_distance += ((m_speed / 1000000000.0) * (double) nanoseconds);
    double slack = section[m_section]->total_distance(m_lane) - m_distance;
    if (slack <= 0.0) {
        m_section = ((m_section + 1) == sections) ? 0 :  m_section + 1;
        m_distance = -slack;
    }
    m_position = section[m_section]->position(m_lane, m_distance);
    m_angle = section[m_section]->angle(m_lane, m_distance);

    printf("Car::advance(%d ns, %d sections):  distance = %5.1lf\n", nanoseconds, sections, m_distance);
    printf("  angle = %5.1lf,  pos = (%5.1lf, %5.1lf, %5.1lf}\n", m_angle, m_position.v1, m_position.v2, m_position.v3);
}

double Car::angle() const
{
    return m_angle - 90.0;
}

Double3 Car::position() const
{
    return m_position;
}

