//
// shape_set.cpp
//
#include "shape_set.h"
#include <algorithm>

ShapeSet::ShapeSet(void)
    : m_shapes(0)
{
    add_shape(Shape().t(0, 0));                                            // shape_id = 0
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(0, 5));    // shape_id = 1
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 4));    // shape_id = 2
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 3));    // shape_id = 3
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 2));    // shape_id = 4
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 5
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(1, 4));    // shape_id = 6
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(1, 4));    // shape_id = 7
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(1, 3));    // shape_id = 8
    add_shape(Shape().t(0, 0).t(1, 0).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 9
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 3).t(1, 3));   // shape_id = 10
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(2, 3));    // shape_id = 11
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(1, 2));    // shape_id = 12
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 13
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(2, 2).t(2, 3));    // shape_id = 14
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 2));    // shape_id = 15
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 2));   // shape_id = 16
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 3));    // shape_id = 17
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 2));    // shape_id = 18
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 3));    // shape_id = 19
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(1, 2).t(1, 3));    // shape_id = 20
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(2, 1).t(2, 2));    // shape_id = 21
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(1, 2).t(2, 1));    // shape_id = 22
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 0).t(1, 3));    // shape_id = 23
    add_shape(Shape().t(0, 0).t(0, 1).t(-1, 1).t(-1, 2).t(1, 1).t(1, 2));  // shape_id = 24
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 1));    // shape_id = 25
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(2, 0));    // shape_id = 26
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // shape_id = 27
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(2, 2));    // shape_id = 28
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 2).t(1, 3));    // shape_id = 29
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(2, 1).t(2, 2));    // shape_id = 30
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 1).t(1, 2));   // shape_id = 31
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 2).t(1, 3));   // shape_id = 32
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // shape_id = 33
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 1).t(1, 2));   // shape_id = 34
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 1).t(1, 2).t(1, 3));   // shape_id = 35
}

ShapeSet::~ShapeSet()
{
}

void ShapeSet::add_shape(const Shape& shape)
{
    if (m_shapes < MAX_SHAPES) {
        m_list[m_shapes] = shape;
        ++m_shapes;
    }
}

int ShapeSet::tiles(int shape_id) const
{
    return m_list[shape_id].tiles();
}

int ShapeSet::posh(int shape_id, int tix, int orientation) const
{
    return m_list[shape_id].posh(tix, orientation);
}

int ShapeSet::posv(int shape_id, int tix, int orientation) const
{
    return m_list[shape_id].posv(tix, orientation);
}

bool ShapeSet::shape_contained(int shape_id, int orientation, int ph, int pv, int dimh, int dimv) const
{
    for (int i = 0; i < tiles(shape_id); i++) {
        int hpos = ph + posh(shape_id, i, orientation);
        if (hpos < 0 || hpos >= dimh)
            return false;
        int vpos = pv + posv(shape_id, i, orientation);
        if (vpos < 0 || vpos >= dimv)
            return false;
    }
    return true;
}

bool ShapeSet::shape_collision(int shape_id1, int orientation1, int ph1, int pv1, int shape_id2, int orientation2, int ph2, int pv2) const
{
    for (int i = 0; i < tiles(shape_id1); i++) {
        int hpos1 = ph1 + posh(shape_id1, i, orientation1);
        int vpos1 = pv1 + posv(shape_id1, i, orientation1);
        for (int j = 0; j < tiles(shape_id2); j++) {
            int hpos2 = ph2 + posh(shape_id2, j, orientation2);
            int vpos2 = pv2 + posv(shape_id2, j, orientation2);
            if (hpos1 == hpos2 && vpos1 == vpos2)
                return true;
        }
    }
    return false;
}

bool ShapeSet::tile_at(int shape_id, int orientation, int x, int y) const
{
    for (int i = 0; i < tiles(shape_id); i++) {
        if (posh(shape_id, i, orientation) == x && posv(shape_id, i, orientation) == y)
            return true;
    }
    return false;
}

int ShapeSet::horz_center(int shape_id, int orientation, int unit_length) const
{
    int maxh = -1000;
    int minh = 1000;
    for (int i = 0; i < tiles(shape_id); i++) {
        maxh = std::max(maxh, posh(shape_id, i, orientation));
        minh = std::min(minh, posh(shape_id, i, orientation));
    }
    return (unit_length * (maxh + minh)) / 2;
}

int ShapeSet::vert_center(int shape_id, int orientation, int unit_length) const
{
    int maxv = -1000;
    int minv = 1000;
    for (int i = 0; i < tiles(shape_id); i++) {
        maxv = std::max(maxv, posv(shape_id, i, orientation));
        minv = std::min(minv, posv(shape_id, i, orientation));
    }
    return (unit_length * (maxv + minv)) / 2;
}


