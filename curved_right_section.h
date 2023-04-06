
#ifndef _CURVED_RIGHT_SECTION_H_
#define _CURVED_RIGHT_SECTION_H_

#include "section.h"
#include "double3.h"

class CurvedRightSection: public Section
{
public:
    CurvedRightSection(int lanes, double radius, double total_angle, Anchor start_anchor);
    virtual ~CurvedRightSection();
    double total_distance(int lane) const;
    double car_yaw(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    Anchor start_anchor() const;
    Anchor end_anchor() const;
    CadModel cad_model() const;
protected:
    double rlane(int lane) const;

private:
    int m_lanes;
    double m_radius;
    double m_total_angle;
    Anchor m_start_anchor;
    Anchor m_end_anchor;
};

#endif // _CURVED_RIGHT_SECTION_SHAPE_
