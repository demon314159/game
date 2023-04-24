
#include "look.h"
#include <string.h>

float Look::dimx = 1.0;
float Look::dimh = 1.0;
float Look::dimb = 0.025;
float Look::dimt = 0.05;

bool Look::m_3d = false;

void Look::process_options(int argv, char** args)
{
    for (int i = 1; i < argv; i++) {
        if (0 == strncmp("-3d", args[i], 3)) {
            set_3d(true);
        }
    }
}

void Look::set_3d(bool v)
{
    m_3d = v;
}

bool Look::get_3d()
{
    return m_3d;
}

PaintCan Look::table_paint()
{
    if (Look::get_3d())
        return PaintCan(0.75, 0.75, 0.75);
    else
        return PaintCan(0.4, 0.8, 1.0);
}

PaintCan Look::grid_paint()
{
    return PaintCan(0.5, 0.5, 0.5);
}

PaintCan Look::brick_paint()
{
    if (Look::get_3d())
        return PaintCan(1.0, 1.0, 1.0);
    else
        return PaintCan(1.0, 0.0, 0.0);
}

