
#ifndef _CURVED_LEFT_SECTION_H_
#define _CURVED_LEFT_SECTION_H_

#include "section.h"
#include "double3.h"
#include "rise_profile.h"

class CurvedLeftSection: public Section
{
public:
    CurvedLeftSection(int lanes, double radius, double total_angle, Anchor start_anchor, double rise = 0.0);
    virtual ~CurvedLeftSection();
    double total_distance(int lane) const;
    double car_yaw(int lane, double distance) const;
    double car_pitch(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    Anchor start_anchor() const;
    Anchor end_anchor() const;
    CadModel cad_model() const;
protected:
    double rlane(int lane) const;

private:
    int m_lanes;
    double m_rise;
    double m_radius;
    double m_total_angle;
    Anchor m_start_anchor;
    Anchor m_end_anchor;
    RiseProfile m_pro;
};

#endif // _CURVED_LEFT_SECTION_SHAPE_
