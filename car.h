#if !defined(_CAR_H_)
#define _CAR_H_

#include "double3.h"
#include "section.h"

class Car
{
public:
    Car();
    ~Car();
    void advance(int nanoseconds, Section** section, int sections);
    double angle() const;
    Double3 position() const;

protected:
    double m_speed;
    int m_section;
    int m_lane;
    double m_distance;
    double m_angle;
    Double3 m_position;
};

#endif // _CAR_H_

