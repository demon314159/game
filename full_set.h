//
// full_set.h
//
#if !defined(_FULL_SET_H_)
#define _FULL_SET_H_

#define MAX_FULL_SET_PIECES 36

#include "piece.h"

class FullSet
{
public:
    FullSet(void);
    ~FullSet();
    void add(const Piece& piece);

protected:
    int m_pieces;
    Piece m_list[MAX_FULL_SET_PIECES];
};

#endif // _FULL_SET_H_
