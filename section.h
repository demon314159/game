
#ifndef _SECTION_H_
#define _SECTION_H_

#include "double3.h"
#include "cad_model.h"

class Section
{
public:
    virtual ~Section();
    virtual double total_distance(int lane) const = 0;
    virtual double car_angle(int lane, double distance) const = 0;
    virtual Double3 car_position(int lane, double distance) const = 0;
    virtual double start_angle() const = 0;
    virtual Double3 start_anchor() const = 0;
    virtual double end_angle() const = 0;
    virtual Double3 end_anchor() const = 0;
    virtual CadModel cad_model() const = 0;
};

#endif // _SECTION_H_
