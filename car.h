#if !defined(_CAR_H_)
#define _CAR_H_

#include "double3.h"

class Car
{
public:
    Car();
    ~Car();
    void advance(int nanoseconds);
    double angle() const;
    Double3 position() const;

protected:
    double m_angle;
    Double3 m_position;
};

#endif // _CAR_H_

