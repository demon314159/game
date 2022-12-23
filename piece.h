//
// piece.h
//
// When a piece is on_board, the fields orientation, posh and posv define its position.
// When a piece is not on_board, no positional information is implied.
// When a piece is locked, it cannot be changed, it will also be on_board.
// A regular move made by the player will be on_board and not locked.
//
#if !defined(_PIECE_H_)
#define _PIECE_H_

#include "shape_set.h"

class Piece
{
public:
    Piece();
    Piece(int shape_id, bool locked, bool on_board, int orientation, int posh, int posv);
    ~Piece();
    int shape_id() const;
    bool locked() const;
    bool on_board() const;
    int orientation() const;
    int posh() const;
    int posv() const;
    bool drop_piece(int orientation, int posh, int posv);
    bool lift_piece();
    void set_orientation(int new_orientation);

protected:
    int m_shape_id;
    bool m_locked;
    bool m_on_board;
    int m_orientation;
    int m_posh;
    int m_posv;
};

#endif // _PIECE_H_
