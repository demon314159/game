//
// fullset.h
//
#if !defined(_FULLSET_H_)
#define _FULLSET_H_

#define MAX_FULLSET_PIECES 128

#include "piece.h"

class FullSet
{
public:
    FullSet(void);
    ~FullSet();
    void add(const Piece& piece);

protected:
    int m_pieces;
    Piece* m_list[MAX_FULLSET_PIECES];
};

#endif // _FULLSET_H_
