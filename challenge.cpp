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

int Challenge::shape_id(int pix) const
{
    return m_piece_list[pix].shape_id();
}

bool Challenge::locked(int pix) const
{
    return m_piece_list[pix].locked();
}

bool Challenge::on_board(int pix) const
{
    return m_piece_list[pix].on_board();
}

int Challenge::orientation(int pix) const
{
    return m_piece_list[pix].orientation();
}

int Challenge::posh(int pix) const
{
    return m_piece_list[pix].posh();
}

int Challenge::posv(int pix) const
{
    return m_piece_list[pix].posv();
}

bool Challenge::drop_piece(const ShapeSet* shape_set, int pix, int orientation, int posh, int posv)
{
    if (!piece_fits(shape_set, pix, orientation, posh, posv))
        return false;
    return m_piece_list[pix].drop_piece(orientation, posh, posv);
}

bool Challenge::lift_piece(int pix)
{
    return m_piece_list[pix].lift_piece();
}

bool Challenge::piece_fits(const ShapeSet* shape_set, int pix, int orientation, int posh, int posv) const
{
    int shape_id = m_piece_list[pix].shape_id();
    if (!shape_set->shape_contained(shape_id, orientation, posh, posv, m_dimh, m_dimv))
        return false;
    for (int i = 0; i < m_pieces; i++) {
        if (i != pix) {
            if (m_piece_list[i].on_board()) {
                if (shape_set->shape_collision(shape_id, orientation, posh, posv, m_piece_list[i].shape_id(), m_piece_list[i].orientation(), m_piece_list[i].posh(), m_piece_list[i].posv()))
                    return false;
            }
        }
    }
    return true;
}

int Challenge::dimh() const
{
    return m_dimh;
}

int Challenge::dimv() const
{
    return m_dimv;
}

void Challenge::set_orientation(int pix, int orientation)
{
    m_piece_list[pix].set_orientation(orientation);
}
