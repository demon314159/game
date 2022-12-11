//
// shape.h
//
#if !defined(_SHAPE_H_)
#define _SHAPE_H_

#define MAX_SHAPE_TILES  6

#include "pos_rec.h"

class Shape
{
public:
    Shape();
    ~Shape();
    Shape& t(int posh, int posv);

protected:
    int m_tiles;
    PosRec m_tile_list[MAX_SHAPE_TILES];
};

#endif // _SHAPE_H_
