//
// challenge.h
//
#if !defined(_CHALLENGE_H_)
#define _CHALLENGE_H_

#define MAX_CHALLENGE_PIECES 10

#include "piece.h"

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
    bool drop_piece(int pix, int orientation, int posh, int posv);
    bool lift_piece(int pix);

protected:
    int m_dimh;
    int m_dimv;
    int m_pieces;
    Piece m_piece_list[MAX_CHALLENGE_PIECES];
};

#endif // _CHALLENGE_H_
