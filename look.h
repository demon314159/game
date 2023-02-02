
#ifndef _LOOK_H_
#define _LOOK_H_

#include "paint_can.h"
#include <QString>

class Look
{
public:
    static void process_options(int argv, char** args);
    static void set_3d(bool v);
    static bool get_3d();
    static float dimx;
    static float dimh;
    static float dimb;
    static float dimt;
    static PaintCan table_paint();
    static PaintCan grid_paint();

private:
    static bool m_3d;
};

#endif // _LOOK_H_
