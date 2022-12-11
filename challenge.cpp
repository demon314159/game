//
// challenge.cpp
//

#include "challenge.h"

Challenge::Challenge(void)
    : m_dimh(0)
    , m_dimv(0)
    , m_pieces(0)
{

}

Challenge::Challenge(int dimh, int dimv)
    : m_dimh(dimh)
    , m_dimv(dimv)
    , m_pieces(0)
{
}

Challenge::~Challenge()
{
}

Challenge Challenge::p(int pid)
{
    Challenge a = *this;
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        a.m_piece_list[m_pieces] = {pid, false, false, 0, 0, 0};
        ++a.m_pieces;
    }
    return a;
}

Challenge Challenge::p(int pid, int orientation, int posh, int posv)
{
    Challenge a = *this;
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        a.m_piece_list[m_pieces] = {pid, true, true, orientation, posh, posv};
        ++a.m_pieces;
    }
    return a;
}

int Challenge::pieces() const
{
    return m_pieces;
}

bool Challenge::solved() const
{
    for (int i = 0; i < m_pieces; i++) {
        if (!m_piece_list[i].on_board)
            return false;
    }
    return true;
}
