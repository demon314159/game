
#include "look.h"

float Look::dimx = 1.0;
float Look::dimh = 1.0;
float Look::dimb = 0.025;
float Look::dimt = 0.05;

PaintCan Look::table_paint()
{
    return PaintCan(0.4, 0.8, 1.0);
}

PaintCan Look::grid_paint()
{
    return PaintCan(0.5, 0.5, 0.5);
}


