#include <cmath>
#include "car.h"

Car::Car()
    : m_angle(0.0)
    , m_position({0.0, 0.0, 0.0})
{
}

Car::~Car()
{
}

void Car::advance(int nanoseconds)
{
    float turns_per_second = 5.0 / 20.0;
    m_angle += ((360.0 * turns_per_second / 1000000000.0) * (double) nanoseconds);
}

double Car::angle() const
{
    return m_angle;
}

Double3 Car::position() const
{
    return m_position;
}

