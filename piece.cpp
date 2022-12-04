//
// piece.cpp
//
#include "piece.h"

Piece::Piece()
    : m_tiles(0)
{
}

Piece::~Piece()
{
}

Piece Piece::t(int posh, int posv)
{
    Piece a = *this;
    if (m_tiles < MAX_PIECE_TILES) {
        a.m_tile_list[m_tiles] = {posh, posv};
        ++a.m_tiles;
    }
    return a;
}

