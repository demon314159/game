#if !defined(_CAR_H_)
#define _CAR_H_

#include "double3.h"
#include "section.h"
#include "cad_model.h"

class Car
{
public:
    Car();
    ~Car();
    void advance(int nanoseconds, Section** section, int sections);
    double yaw() const;
    double pitch() const;
    Double3 position() const;
    CadModel cad_model() const;

protected:
    double m_speed;
    int m_section;
    int m_lane;
    double m_distance;
    double m_yaw;
    double m_pitch;
    Double3 m_position;
    void build_car(CadModel* vehicle) const;
    void build_wheels(CadModel* vehicle) const;
    CadModel build_wheel(float r_tire, float r_rim, float r_inner, float r_spacer, float width) const;
};

#endif // _CAR_H_

