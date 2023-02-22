
#ifndef _STRAIGHT_SECTION_H_
#define _STRAIGHT_SECTION_H_

#include "section.h"
#include "double3.h"

class StraightSection: public Section
{
public:
    StraightSection(int lanes, double length, double start_angle, Double3 start_anchor);
    virtual ~StraightSection();
    double total_distance(int lane) const;
    double angle(int lane, double distance) const;
    Double3 position(int lane, double distance) const;
    double start_angle() const;
    Double3 start_anchor() const;
    double end_angle() const;
    Double3 end_anchor() const;

private:
    int m_lanes;
    double m_length;
    double m_start_angle;
    Double3 m_start_anchor;
    double m_end_angle;
    Double3 m_end_anchor;
};

#endif // _STRAIGHT_SECTION_SHAPE_
