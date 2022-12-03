//
// challenge.cpp
//
#include "challenge.h"

#include "stdio.h"

Challenge::Challenge(int dimv, int dimh)
    : m_dimv(dimv)
    , m_dimh(dimh)
    , m_pieces(0)
{
}

Challenge Challenge::p(int v)
{
    Challenge a = *this;
    if (m_pieces < MAX_PIECES) {
        a.m_list[m_pieces] = v;
        ++a.m_pieces;
    }
    return a;
}

void Challenge::show()
{
    printf("Pieces = %d: ( ", m_pieces);
    for (int i = 0; i < m_pieces; i++) {
        printf("%d ", m_list[i]);
    }
    printf(")\n");
}

