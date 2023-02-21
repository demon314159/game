
#ifndef _STRAIGHT_SECTION_H_
#define _STRAIGHT_SECTION_H_

#include "section.h"
#include "double3.h"

class StraightSection: public Section
{
public:
    StraightSection(int lanes, double length, double angle, Double3 anchor);
    virtual ~StraightSection();
    double total_distance(int lane) const;
    double angle(int lane, double distance) const;
    Double3 position(int lane, double distance) const;

private:
    int m_lanes;
    double m_length;
    double m_angle;
    Double3 m_anchor;

};

#endif // _STRAIGHT_SECTION_SHAPE_
