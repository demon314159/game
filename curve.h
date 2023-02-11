
#ifndef _CURVE_H_
#define _CURVE_H_

#include "radial.h"

class Curve
{
    static const int MAX_RADIALS = 16;
public:
    Curve();
    ~Curve();
    void add(const Radial& rad);
    int steps() const;
    double x(int step) const;
    double y(int step) const;

protected:

private:
    int m_radials;
    Radial m_radial[MAX_RADIALS];

};

#endif // _CURVE_H_
