
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "facet.h"

class Shape
{
public:
    virtual int facets() const = 0;
    virtual Facet facet(int facet_ix) const = 0;
};

#endif // _SHAPE_H_
