#if !defined(_TRACK_H_)
#define _TRACK_H_

#include "car.h"
#include "double3.h"

class Track
{
public:
    static const int MAX_CARS = 8;
    Track();
    ~Track();
    int cars() const;
    void advance(int nanoseconds);
    double car_angle(int car_id) const;
    Double3 car_position(int car_id) const;

protected:
    int m_cars;
    Car m_car[MAX_CARS];
};

#endif // _TRACK_H_

