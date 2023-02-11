
#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "double3.h"
#include "matrix.h"

class Radial
{
public:
    Radial();
    Radial(Double2 p1, Double2 p2, Double2 p3, int steps);
    Radial(Double2 p1, Double2 p2, double c, int steps);
    Radial(const Radial& rad1, const Radial& rad2, int steps);
    ~Radial();
    int steps() const;
    double x(double fract) const;
    double y(double fract) const;
    double x(int step) const;
    double y(int step) const;
    Radial shrunk(double fract1, double fract2) const;

protected:
    double mag(double x, double y) const;
    Double2 midpoint(Double2 p1, Double2 p2) const;
    double angle(double fract) const;
    double radius(double fract) const;

private:
    int m_steps;
    Double2 m_center;
    double m_start_radius;
    double m_end_radius;
    double m_start_angle;
    double m_end_angle;
};

#endif // _RADIAL_H_
