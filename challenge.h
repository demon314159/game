//
// challenge.h
//
#if !defined(_CHALLENGE_H_)
#define _CHALLENGE_H_

#define MAX_CHALLENGE_PIECES 32

#include "moverec.h"

class Challenge
{
public:
    Challenge(int dimh, int dimv);
    ~Challenge();
    Challenge p(int pid);
    Challenge p(int pid, int orientation, int posh, int posv);

protected:
    int m_dimh;
    int m_dimv;
    int m_pieces;
    int m_hints;
    int m_piece_list[MAX_CHALLENGE_PIECES];
    MoveRec m_hint_list[MAX_CHALLENGE_PIECES];
};

#endif // _CHALLENGE_H_
