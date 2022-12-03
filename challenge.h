//
// challenge.h
//
#if !defined(_CHALLENGE_H_)
#define _CHALLENGE_H_

#define MAX_PIECES 32

class Challenge
{
public:
    Challenge(int dimv, int dimh);
    Challenge p(int v);
    void show();

protected:
    int m_dimv;
    int m_dimh;
    int m_pieces;
    int m_list[MAX_PIECES];
};

#endif // _CHALLENGE_H_
