
#ifndef _CURVED_SECTION_H_
#define _CURVED_SECTION_H_

#include "section.h"
#include "double3.h"

class CurvedSection: public Section
{
public:
    CurvedSection(int lanes, double radius, double total_angle, double start_angle, Double3 start_anchor);
    virtual ~CurvedSection();
    double total_distance(int lane) const;
    double car_angle(int lane, double distance) const;
    Double3 car_position(int lane, double distance) const;
    double start_angle() const;
    Double3 start_anchor() const;
    double end_angle() const;
    Double3 end_anchor() const;
    CadModel cad_model() const;

private:
    int m_lanes;
    double m_radius;
    double m_total_angle;
    double m_start_angle;
    Double3 m_start_anchor;
    double m_end_angle;
    Double3 m_end_anchor;
};

#endif // _CURVED_SECTION_SHAPE_
