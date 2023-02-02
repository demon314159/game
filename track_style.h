
#ifndef _TRACK_STYLE_H_
#define _TRACK_STYLE_H_

#include "paint_can.h"

class TrackStyle
{
public:
    static float car_width;
    static float car_gap;
    static float car_shoulder;
    static float track_height;
    static float track_bevel;
    static float slot_height;
    static float slot_width;
    static float rail_width;
    static PaintCan track_paint();
    static PaintCan slot_paint();
    static PaintCan rail_paint();

private:
};

#endif // _TRACK_STYLE_H_
