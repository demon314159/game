
#ifndef _SECTION_H_
#define _SECTION_H_

#include "double3.h"

class Section
{
public:
    virtual ~Section();
    virtual double total_distance(int lane) const = 0;
    virtual double angle(int lane, double distance) const = 0;
    virtual Double3 position(int lane, double distance) const = 0;
};

#endif // _SECTION_H_
