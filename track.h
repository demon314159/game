#if !defined(_TRACK_H_)
#define _TRACK_H_

#include "car.h"
#include "double3.h"
#include "section.h"

class Track
{
public:
    static const int MAX_SECTIONS = 32;
    static const int MAX_CARS = 8;
    Track();
    ~Track();
    int cars() const;
    void advance(int nanoseconds);
    double car_angle(int car_id) const;
    Double3 car_position(int car_id) const;
    void add_section(Section* section);
    int sections() const;
    Section* section(int ix);
    Car* car(int ix);

protected:
    int m_cars;
    Car m_car[MAX_CARS];
    int m_sections;
    Section* m_section[MAX_SECTIONS];
};

#endif // _TRACK_H_

