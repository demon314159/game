
#include "look.h"

float Look::dimx = 1.0;
float Look::dimh = 2.0 / 3.0;
PaintCan Look::red_paint(1.0, 0.0, 0.0);
PaintCan Look::green_paint(0.0, 0.8, 0.2);
PaintCan Look::blue_paint(0.0, 0.0, 1.0);
PaintCan Look::white_paint(1.0, 1.0, 1.0);
PaintCan Look::black_paint(0.0, 0.0, 0.0);
PaintCan Look::done_paint(0.0, 0.7, 0.3);
PaintCan Look::cancel_paint(1.0, 0.0, 0.0);
PaintCan Look::background_paint(1.0, 192.0 / 256.0, 203.0 / 256.0); // pink
PaintCan Look::grid_paint(0.5, 0.5, 0.5);


//PaintCan Look::door_paint(133.0 / 256.0, 94.0 / 256.0, 66.0 / 256.0);
PaintCan Look::door_paint(1.0, 1.0, 1.0);

PaintCan Look::frame_paint(1.0, 1.0, 1.0);

//PaintCan Look::glass_paint(0.0, 0.0, 0.0);
//PaintCan Look::glass_paint(1.0, 1.0, 1.0);
PaintCan Look::glass_paint(0.96, 0.99, 1.0);


float Look::glass_animation_id = 99.0;
