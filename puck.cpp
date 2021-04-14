//
// puck.cpp
//
#include "puck.h"
#include <math.h>

Puck::Puck(double velocity_x, double velocity_y)
    : m_velocity_x(velocity_x)
    , m_velocity_y(velocity_y)
{
}

double Puck::velocity_x() const
{
    return m_velocity_x;
}

double Puck::velocity_y() const
{
    return m_velocity_y;
}


