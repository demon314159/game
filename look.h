
#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

class Look
{
public:
    static float dimx;
    static float dimh;
    static float dimb;
    static float dimt;
    static PaintCan table_paint();
    static PaintCan grid_paint();
};

#endif // _LOOK_H_
