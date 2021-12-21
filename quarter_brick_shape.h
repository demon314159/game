
#ifndef _QUARTER_BRICK_SHAPE_H_
#define _QUARTER_BRICK_SHAPE_H_

#include "brick_shape.h"
#include "float3.h"
#include "facet.h"

class QuarterBrickShape: public BrickShape
{
public:
    QuarterBrickShape(float dimx, float dimy, float dimz, float dimb);
    virtual ~QuarterBrickShape();

private:
    void define_shape() override;
};

#endif // _iQUARTER_BRICK_SHAPE_
