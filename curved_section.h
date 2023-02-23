
#ifndef _CURVED_SECTION_H_
#define _CURVED_SECTION_H_

#include "section.h"
#include "double3.h"

class CurvedSection: public Section
{
public:
    CurvedSection(int lanes, double radius, double total_angle, Anchor start_anchor);
    virtual ~CurvedSection();
    double total_distance(int lane) const;
    double car_angle(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    Anchor start_anchor() const;
    Anchor end_anchor() const;
    CadModel cad_model() const;

private:
    int m_lanes;
    double m_radius;
    double m_total_angle;
    Anchor m_start_anchor;
    Anchor m_end_anchor;
};

#endif // _CURVED_SECTION_SHAPE_
