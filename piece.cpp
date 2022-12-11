//
// piece.cpp
//
#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(int shape_id, bool locked, bool on_board, int orientation, int posh, int posv)
    : m_shape_id(shape_id)
    , m_locked(locked)
    , m_on_board(on_board)
    , m_orientation(orientation)
    , m_posh(posh)
    , m_posv(posv)
{
}

Piece::~Piece()
{
}

int Piece::shape_id() const
{
    return m_shape_id;
}

bool Piece::locked() const
{
    return m_locked;
}

bool Piece::on_board() const
{
    return m_on_board;
}

int Piece::orientation() const
{
    return m_orientation;
}

int Piece::posh() const
{
    return m_posh;
}

int Piece::posv() const
{
    return m_posv;
}

