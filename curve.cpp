
#include <cmath>
#include "stdlib.h"
#include "stdio.h"
#include "curve.h"

Curve::Curve()
    : m_radials(0)
{
}

Curve::~Curve()
{
}

void Curve::add(const Radial& rad)
{
    if (m_radials < MAX_RADIALS) {
        m_radial[m_radials] = rad;
        ++m_radials;
    }
}

int Curve::steps() const
{
    int total = 0;
    for (int i = 0; i < m_radials; i++) {
        total += m_radial[i].steps();
    }
    return total;
}

double Curve::x(int step) const
{
    for (int i = 0; i < m_radials; i++) {
        if (step >= m_radial[i].steps()) {
            step -= m_radial[i].steps();
        } else {
            return m_radial[i].x(step);
        }
    }
    return 0.0;
}

double Curve::y(int step) const
{
    for (int i = 0; i < m_radials; i++) {
        if (step >= m_radial[i].steps()) {
            step -= m_radial[i].steps();
        } else {
            return m_radial[i].y(step);
        }
    }
    return 0.0;
}
