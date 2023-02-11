
#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "radial.h"
#include "matrix.h"

#define PI 3.1415926535898

Radial::Radial()
    : m_steps(0)
    , m_center({0.0, 0.0})
    , m_start_radius(1.0)
    , m_end_radius(1.0)
    , m_start_angle(0.0)
    , m_end_angle(0.0)
{
}

Radial::Radial(Double2 p1, Double2 p2, Double2 p3, int steps)
    : m_steps(steps)
    , m_center({0.0, 0.0})
    , m_start_radius(1.0)
    , m_end_radius(1.0)
    , m_start_angle(0.0)
    , m_end_angle(0.0)
{
    Double2 mpa = midpoint(p1, p2);
    Double2 mpb = midpoint(p2, p3);
    Matrix m(2, 2);
    m.set(0, 0,  (p2.v2 - p1.v2));
    m.set(0, 1, -(p3.v2 - p2.v2));
    m.set(1, 0, -(p2.v1 - p1.v1));
    m.set(1, 1,  (p3.v1 - p2.v1));
    Matrix w = m.inverse();
    Matrix z(2, 1);
    z.set(0, 0, mpb.v1 - mpa.v1);
    z.set(1, 0, mpb.v2 - mpa.v2);
    Matrix s = w * z;
    m_center = {mpa.v1 + s.get(0,0) * (p2.v2 - p1.v2), mpa.v2 - s.get(0,0) * (p2.v1 - p1.v1)};
    m_start_radius = mag(p1.v1 - m_center.v1, p1.v2 - m_center.v2);
    m_end_radius = m_start_radius;
    m_start_angle = atan2(p1.v2 - m_center.v2, p1.v1 - m_center.v1);
    m_end_angle = atan2(p3.v2 - m_center.v2, p3.v1 - m_center.v1);
}

Radial::Radial(Double2 p1, Double2 p2, double c, int steps)
    : m_steps(steps)
    , m_center({0.0, 0.0})
    , m_start_radius(1.0)
    , m_end_radius(1.0)
    , m_start_angle(0.0)
    , m_end_angle(0.0)
{
    Double2 mpa = midpoint(p1, p2);
    double lmag  = mag(p1.v1 - p2.v1, p1.v2 - p2.v2);
    m_center = {c * (p2.v2 - p1.v2) / lmag + mpa.v1, -c * (p2.v1 - p1.v1) / lmag + mpa.v2};

    m_start_radius = mag(p1.v1 - m_center.v1, p1.v2 - m_center.v2);
    m_end_radius = m_start_radius;
    m_start_angle = atan2(p1.v2 - m_center.v2, p1.v1 - m_center.v1);
    m_end_angle = atan2(p2.v2 - m_center.v2, p2.v1 - m_center.v1);
}

Radial::Radial(const Radial& rad1, const Radial& rad2, int steps)
    : m_steps(steps)
    , m_center({0.0, 0.0})
    , m_start_radius(1.0)
    , m_end_radius(1.0)
    , m_start_angle(0.0)
    , m_end_angle(0.0)
{
    double x1 = rad1.x(1.0);
    double y1 = rad1.y(1.0);
    double x2 = rad2.x(0.0);
    double y2 = rad2.y(0.0);

    Matrix m(2, 2);
    m.set(0, 0,  (x1 - rad1.m_center.v1));
    m.set(0, 1, -(x2 - rad2.m_center.v1));
    m.set(1, 0,  (y1 - rad1.m_center.v2));
    m.set(1, 1, -(y2 - rad2.m_center.v2));
    Matrix w = m.inverse();
    Matrix z(2, 1);
    z.set(0, 0, rad2.m_center.v1 - rad1.m_center.v1);
    z.set(1, 0, rad2.m_center.v2 - rad1.m_center.v2);
    Matrix s = w * z;
    double xi = rad1.m_center.v1 + s.get(0,0) * (x1 - rad1.m_center.v1);
    double yi = rad1.m_center.v2 + s.get(0,0) * (y1 - rad1.m_center.v2);
    m_center = {xi, yi};
    m_start_radius = mag(x1 - xi, y1 - yi);
    m_end_radius = mag(x2 - xi, y2 - yi);
    m_start_angle = atan2(y1 - yi, x1 - xi);
    m_end_angle = atan2(y2 - yi, x2 - xi);
    if (m_end_angle > m_start_angle) {
        m_start_angle += (2.0 * PI);
    }
}

Radial::~Radial()
{
}

double Radial::mag(double x, double y) const
{
    return sqrt(x * x + y * y);
}

Double2 Radial::midpoint(Double2 p1, Double2 p2) const
{
    Double2 mp = {(p1.v1 + p2.v1) / 2.0, (p1.v2 + p2.v2) / 2.0};
    return mp;
}

double Radial::angle(double fract) const
{
    return m_start_angle + fract * (m_end_angle - m_start_angle);
}

double Radial::radius(double fract) const
{
    double a = -PI / 2.0 + fract * PI;
    return ((m_end_radius - m_start_radius) / 2.0) * sin(a) + (m_end_radius + m_start_radius) / 2.0;
}

int Radial::steps() const
{
    return m_steps;
}

double Radial::x(double fract) const
{
    return m_center.v1 + radius(fract) * cos(m_start_angle + fract * (m_end_angle - m_start_angle));
}

double Radial::y(double fract) const
{
    return m_center.v2 + radius(fract) * sin(m_start_angle + fract * (m_end_angle - m_start_angle));
}

double Radial::x(int step) const
{
    double fract = (double) step / (double) (m_steps - 1);
    return m_center.v1 + radius(fract) * cos(m_start_angle + fract * (m_end_angle - m_start_angle));
}

double Radial::y(int step) const
{
    double fract = (double) step / (double) (m_steps - 1);
    return m_center.v2 + radius(fract) * sin(m_start_angle + fract * (m_end_angle - m_start_angle));
}

Radial Radial::shrunk(double fract1, double fract2) const
{
    Radial rad = *this;
    rad.m_start_angle = angle(fract1);
    rad.m_end_angle = angle(fract2);
    rad.m_start_radius = radius(fract1);
    rad.m_end_radius = radius(fract2);
    return rad;
}
