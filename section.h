
#ifndef _SECTION_H_
#define _SECTION_H_

#include "double3.h"
#include "anchor.h"
#include "cad_model.h"

class Section
{
public:
    virtual ~Section();
    virtual double total_distance(int lane) const = 0;
    virtual double car_yaw(int lane, double distance) const = 0;
    virtual double car_pitch(int lane, double distance) const = 0;
    virtual Double3 car_position(int lane, double distance) const = 0;
    virtual Anchor start_anchor() const = 0;
    virtual Anchor end_anchor() const = 0;
    virtual CadModel cad_model() const = 0;
};

#endif // _SECTION_H_
