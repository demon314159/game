
#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"

class Look
{
public:
    static void process_options(int argv, char** args);
    static float dimx;
    static float dimh;
    static PaintCan table_paint();
    static PaintCan marker_paint();
    static PaintCan grid_paint();
    static PaintCan brick_paint();
    static PaintCan ledge_paint();
    static PaintCan frame_paint();
    static PaintCan window_paint();
    static PaintCan door_paint();
    static PaintCan roof_paint();
    static PaintCan vbutton_paint();
    static PaintCan cancel_paint();
    static PaintCan done_paint();
    static PaintCan vbackground_paint();
    static PaintCan glass_paint();
    static float glass_animation_id();
    static void set_3d(bool v);
    static bool get_3d();

private:
    static bool m_3d;
};

#endif // _LOOK_H_
