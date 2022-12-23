//
// challenge.h
//
#if !defined(_CHALLENGE_H_)
#define _CHALLENGE_H_

#define MAX_CHALLENGE_PIECES 10

#include "piece.h"
#include "shape_set.h"

class Challenge
{
public:
    Challenge(void);
    Challenge(int dimh, int dimv);
    ~Challenge();
    Challenge& p(int shape_id);
    Challenge& p(int shape_id, int orientation, int posh, int posv);
    bool solved() const;

    int pieces() const;
    int shape_id(int pix) const;
    bool locked(int pix) const;
    bool on_board(int pix) const;
    int orientation(int pix) const;
    int posh(int pix) const;
    int posv(int pix) const;
    bool drop_piece(const ShapeSet* shape_set, int pix, int orientation, int posh, int posv);
    bool lift_piece(int pix);
    int dimh() const;
    int dimv() const;
    void set_orientation(int pix, int orientation);

protected:
    int m_dimh;
    int m_dimv;
    int m_pieces;
    Piece m_piece_list[MAX_CHALLENGE_PIECES];

    bool piece_fits(const ShapeSet* shape_set, int pix, int orientation, int posh, int posv) const;
};

#endif // _CHALLENGE_H_
