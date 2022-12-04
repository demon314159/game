//
// fillset.cpp
//
#include "fullset.h"

FullSet::FullSet(void)
    : m_pieces(0)
{
    add(Piece().t(0, 0).t(0,1).t(0,2).t(0,3).t(0, 4).t(0, 5));
}

FullSet::~FullSet()
{
    for (int i = 0; i < m_pieces; i++) {
        delete m_list[i];
    }
}

void FullSet::add(const Piece& piece)
{
    if (m_pieces < MAX_FULLSET_PIECES) {
        m_list[m_pieces] = new Piece(piece);
        ++m_pieces;
    }
}


