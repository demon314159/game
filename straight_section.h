
#ifndef _STRAIGHT_SECTION_H_
#define _STRAIGHT_SECTION_H_

#include "section.h"
#include "double3.h"
#include "rise_profile.h"

class StraightSection: public Section
{
public:
    StraightSection(int lanes, double length, Anchor start_anchor, double rise = 0.0);
    virtual ~StraightSection();
    double total_distance(int lane) const;
    double car_yaw(int lane, double distance) const;
    double car_pitch(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    Anchor start_anchor() const;
    Anchor end_anchor() const;
    CadModel cad_model() const;

private:
    int m_lanes;
    double m_rise;
    double m_length;
    Anchor m_start_anchor;
    Anchor m_end_anchor;
    RiseProfile m_pro;
};

#endif // _STRAIGHT_SECTION_SHAPE_
