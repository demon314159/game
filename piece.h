//
// piece.h
//
#if !defined(_PIECE_H_)
#define _PIECE_H_

#define MAX_PIECE_TILES  6

#include "posrec.h"

class Piece
{
public:
    Piece();
    ~Piece();
    Piece t(int posh, int posv);

protected:
    int m_tiles;
    PosRec m_tile_list[MAX_PIECE_TILES];
};

#endif // _PIECE_H_
