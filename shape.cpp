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

int Shape::tiles() const
{
    return m_tiles;
}

int Shape::posh(int tix, int orientation) const
{
    switch(orientation) {
        case 0: return  m_tile_list[tix].posh;
                break;
        case 1: return  m_tile_list[tix].posv;
                break;
        case 2: return -m_tile_list[tix].posh;
                break;
        case 3: return -m_tile_list[tix].posv;
                break;
        case 4: return -m_tile_list[tix].posh;
                break;
        case 5: return  m_tile_list[tix].posv;
                break;
        case 6: return  m_tile_list[tix].posh;
                break;
        case 7: return -m_tile_list[tix].posv;
                break;
        default: return 0;
    }
}

int Shape::posv(int tix, int orientation) const
{
    switch(orientation) {
        case 0: return  m_tile_list[tix].posv;
                break;
        case 1: return -m_tile_list[tix].posh;
                break;
        case 2: return -m_tile_list[tix].posv;
                break;
        case 3: return  m_tile_list[tix].posh;
                break;
        case 4: return  m_tile_list[tix].posv;
                break;
        case 5: return  m_tile_list[tix].posh;
                break;
        case 6: return -m_tile_list[tix].posv;
                break;
        case 7: return -m_tile_list[tix].posh;
                break;
        default: return 0;
    }
}


