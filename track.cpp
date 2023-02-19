#include <cmath>
#include "track.h"

Track::Track()
    : m_cars(2)
{
}

Track::~Track()
{
}

int Track::cars() const
{
    return m_cars;
}

void Track::advance(int nanoseconds)
{
    for (int i = 0; i < m_cars; i++) {
        m_car[i].advance(nanoseconds);
    }
}

double Track::car_angle(int car_id) const
{
    return m_car[car_id].angle();
}

Double3 Track::car_position(int car_id) const
{
    return m_car[car_id].position();
}

