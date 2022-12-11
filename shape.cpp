//
// shape.cpp
//
#include "shape.h"

Shape::Shape()
    : m_tiles(0)
{
}

Shape::~Shape()
{
}

Shape Shape::t(int posh, int posv)
{
    Shape a = *this;
    if (m_tiles < MAX_SHAPE_TILES) {
        a.m_tile_list[m_tiles] = {posh, posv};
        ++a.m_tiles;
    }
    return a;
}

