
#include "track_style.h"

float TrackStyle::car_width = 1.0;
float TrackStyle::car_gap = 0.25;
float TrackStyle::car_shoulder = 0.25;
float TrackStyle::track_height = 0.1;
float TrackStyle::track_bevel = 0.025;
float TrackStyle::slot_height = 0.05;
float TrackStyle::slot_width = 0.125;
float TrackStyle::rail_width = 0.0625;

PaintCan TrackStyle::track_paint()
{
    return PaintCan(0.25, 0.25, 0.25);
}

PaintCan TrackStyle::slot_paint()
{
    return PaintCan(1.0, 0.0, 0.0);
}

PaintCan TrackStyle::rail_paint()
{
    return PaintCan(0.75, 0.75, 0.75);
}


