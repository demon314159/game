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

Challenge& Challenge::p(int shape_id)
{
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        m_piece_list[m_pieces] = Piece(shape_id, false, false, 0, 0, 0);
        ++m_pieces;
    }
    return *this;
}

Challenge& Challenge::p(int shape_id, int orientation, int posh, int posv)
{
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        m_piece_list[m_pieces] = Piece(shape_id, true, true, orientation, posh, posv);
        ++m_pieces;
    }
    return *this;
}

bool Challenge::solved() const
{
    for (int i = 0; i < m_pieces; i++) {
        if (!m_piece_list[i].on_board())
            return false;
    }
    return true;
}

int Challenge::pieces() const
{
    return m_pieces;
}

bool Challenge::drop_piece(int pix, int orientation, int posh, int posv)
{
    if (pix >= m_pieces)
        return false;
    return m_piece_list[pix].drop_piece(orientation, posh, posv);
}

bool Challenge::lift_piece(int pix)
{
    if (pix >= m_pieces)
        return false;
    return m_piece_list[pix].lift_piece();
}

