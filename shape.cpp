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

Shape& Shape::t(int posh, int posv)
{
    if (m_tiles < MAX_SHAPE_TILES) {
        m_tile_list[m_tiles] = {posh, posv};
        ++m_tiles;
    }
    return *this;
}

