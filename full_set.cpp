//
// full_set.cpp
//
#include "full_set.h"

FullSet::FullSet(void)
    : m_pieces(0)
{
    add(Piece().t(0, 0));                                            // pid = 0
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(0, 5));    // pid = 1
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 4));    // pid = 2
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 3));    // pid = 3
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 2));    // pid = 4
    add(Piece().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // pid = 5
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(1, 4));    // pid = 6
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(1, 4));    // pid = 7
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(1, 3));    // pid = 8
    add(Piece().t(0, 0).t(1, 0).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // pid = 9
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 3).t(1, 3));   // pid = 10
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(2, 3));    // pid = 11
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(1, 2));    // pid = 12
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 3));    // pid = 13
    add(Piece().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(2, 2).t(2, 3));    // pid = 14
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 2));    // pid = 15
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 2));   // pid = 16
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 3));    // pid = 17
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 2));    // pid = 18
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 3));    // pid = 19
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(1, 2).t(1, 3));    // pid = 20
    add(Piece().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(2, 1).t(2, 2));    // pid = 21
    add(Piece().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(1, 2).t(2, 1));    // pid = 22
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 0).t(1, 3));    // pid = 23
    add(Piece().t(0, 0).t(0, 1).t(-1, 1).t(-1, 2).t(1, 1).t(1, 2));  // pid = 24
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 1));    // pid = 25
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(2, 0));    // pid = 26
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // pid = 27
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(2, 2));    // pid = 28
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 2).t(1, 3));    // pid = 29
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(2, 1).t(2, 2));    // pid = 30
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 1).t(1, 2));   // pid = 31
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 2).t(1, 3));   // pid = 32
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // pid = 33
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 1).t(1, 2));   // pid = 34
    add(Piece().t(0, 0).t(0, 1).t(0, 2).t(-1, 1).t(1, 2).t(1, 3));   // pid = 35
}

FullSet::~FullSet()
{
}

void FullSet::add(const Piece& piece)
{
    if (m_pieces < MAX_FULL_SET_PIECES) {
        m_list[m_pieces] = piece;
        ++m_pieces;
    }
}


