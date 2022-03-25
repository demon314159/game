
#include "look.h"
#include <string.h>
#include <stdio.h>

float Look::dimx = 1.0;
float Look::dimh = 2.0 / 3.0;

bool Look::m_3d = false;
QString Look::m_startup_name(".default.brk");
QString Look::m_session_name(".default.brk");

void Look::process_options(int argv, char** args)
{
    for (int i = 1; i < argv; i++) {
        if (0 == strncmp("-3d", args[i], 3)) {
            set_3d(true);
        }
    }
    for (int i = 1; i < argv; i++) {
        QString s(args[i]);
        if (!s.contains('-')) {
            if (s.contains('.')) {
                m_startup_name = s;
            } else {
                m_startup_name = s + QString(".brk");
            }
            printf("file name = '%s'\n", m_startup_name.toLatin1().data());
            return;
        }
    }
}

QString Look::startup_name()
{
    return m_startup_name;
}

QString Look::session_name()
{
    return m_session_name;
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
