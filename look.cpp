
#include "look.h"

float Look::dimx = 1.0;
float Look::dimh = 2.0 / 3.0;

PaintCan Look::table_paint(0.4, 0.8, 1.0);
PaintCan Look::grid_paint(0.5, 0.5, 0.5);
PaintCan Look::marker_paint(0.0, 1.0, 0.0);
PaintCan Look::brick_paint(1.0, 0.0, 0.0);
PaintCan Look::ledge_paint(0.8, 0.8, 0.8);
PaintCan Look::frame_paint(1.0, 1.0, 1.0);
PaintCan Look::window_paint(1.0, 1.0, 1.0);
PaintCan Look::door_paint(1.0, 1.0, 1.0);
PaintCan Look::roof_paint(0.0, 0.8, 0.2);
PaintCan Look::vbutton_paint(0.0, 0.0, 1.0);
PaintCan Look::vbackground_paint(1.0, 192.0 / 256.0, 203.0 / 256.0); // pink
PaintCan Look::done_paint(0.0, 0.7, 0.3);
PaintCan Look::cancel_paint(1.0, 0.0, 0.0);
PaintCan Look::glass_paint(0.96, 0.99, 1.0);
float Look::glass_animation_id = 99.0;
