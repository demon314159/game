
#ifndef _STRAIGHT_SECTION_H_
#define _STRAIGHT_SECTION_H_

#include "section.h"
#include "double3.h"

class StraightSection: public Section
{
public:
    StraightSection(int lanes, double length, Anchor start_anchor);
    virtual ~StraightSection();
    double total_distance(int lane) const;
    double car_angle(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    Anchor start_anchor() const;
    Anchor end_anchor() const;
    CadModel cad_model() const;

private:
    int m_lanes;
    double m_length;
    Anchor m_start_anchor;
    Anchor m_end_anchor;
};

#endif // _STRAIGHT_SECTION_SHAPE_
