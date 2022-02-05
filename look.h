
#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

class Look
{
public:
    static float dimx;
    static float dimh;
    static PaintCan red_paint;
    static PaintCan green_paint;
    static PaintCan blue_paint;
    static PaintCan white_paint;
    static PaintCan black_paint;
    static PaintCan done_paint;
    static PaintCan cancel_paint;
    static PaintCan background_paint;
    static PaintCan grid_paint;
    static PaintCan door_paint;
    static PaintCan frame_paint;
    static PaintCan glass_paint;
    static float glass_animation_id;
};

#endif // _LOOK_H_
