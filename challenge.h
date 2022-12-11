//
// challenge.h
//
#if !defined(_CHALLENGE_H_)
#define _CHALLENGE_H_

#define MAX_CHALLENGE_PIECES 10

#include "moverec.h"

class Challenge
{
public:
    Challenge(void);
    Challenge(int dimh, int dimv);
    ~Challenge();
    Challenge p(int pid);
    Challenge p(int pid, int orientation, int posh, int posv);
    bool solved() const;

    int pieces() const;

protected:
    int m_dimh;
    int m_dimv;
    int m_pieces;
    MoveRec m_piece_list[MAX_CHALLENGE_PIECES];
};

#endif // _CHALLENGE_H_
