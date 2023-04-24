
#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

class Look
{
public:
    static void process_options(int argv, char** args);
    static float dimx;
    static float dimh;
    static float dimb;
    static float dimt;
    static PaintCan table_paint();
    static PaintCan grid_paint();
    static PaintCan brick_paint();

private:
    static bool m_3d;
};

#endif // _LOOK_H_
