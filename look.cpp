
#include "look.h"

float Look::dimx = 1.0;
float Look::dimh = 2.0 / 3.0;

bool Look::m_3d = false;

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

PaintCan Look::marker_paint()
{
    if (Look::get_3d())
        return PaintCan(0.6, 0.6, 0.6);
    else
        return PaintCan(0.0, 1.8, 0.0);
}

PaintCan Look::grid_paint()
{
    return PaintCan(0.5, 0.5, 0.5);
}

PaintCan Look::brick_paint()
{
    return PaintCan(1.0, 0.0, 0.0);
}

PaintCan Look::ledge_paint()
{
    return PaintCan(0.8, 0.8, 0.8);
}

PaintCan Look::frame_paint()
{
    return PaintCan(1.0, 1.0, 1.0);
}

PaintCan Look::window_paint()
{
    return PaintCan(1.0, 1.0, 1.0);
}

PaintCan Look::door_paint()
{
    return PaintCan(1.0, 1.0, 1.0);
}

PaintCan Look::roof_paint()
{
    return PaintCan(0.0, 0.8, 0.2);
}

PaintCan Look::vbutton_paint()
{
    if (Look::get_3d())
        return PaintCan(0.0, 0.0, 0.0);
    else
        return PaintCan(0.0, 0.0, 1.0);
}

PaintCan Look::cancel_paint()
{
    if (Look::get_3d())
        return PaintCan(0.0, 0.0, 0.0);
    else
        return PaintCan(1.0, 0.0, 0.0);
}

PaintCan Look::done_paint()
{
    if (Look::get_3d())
        return PaintCan(0.0, 0.0, 0.0);
    else
        return PaintCan(0.0, 0.7, 0.3);
}

PaintCan Look::vbackground_paint()
{
    if (Look::get_3d())
        return PaintCan(0.5, 0.5, 0.5);
    else
        return PaintCan(1.0, 192.0 / 256.0, 203.0 / 256.0); // pink
}

PaintCan Look::glass_paint()
{
    if (Look::get_3d())
        return PaintCan(0.96, 0.96, 0.96);
    else
        return PaintCan(0.96, 0.99, 1.0);
}

float Look::glass_animation_id()
{
    return 99.0;
}
