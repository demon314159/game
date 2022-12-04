//
// challenge.cpp
//
#include "challenge.h"

#include "stdio.h"

Challenge::Challenge(int dimh, int dimv)
    : m_dimh(dimh)
    , m_dimv(dimv)
    , m_pieces(0)
    , m_hints(0)
{
}

Challenge Challenge::p(int pid)
{
    Challenge a = *this;
    if (m_pieces < MAX_PIECES) {
        a.m_piece_list[m_pieces] = pid;
        ++a.m_pieces;
    }
    return a;
}

Challenge Challenge::h(int pid, int orientation, int posh, int posv)
{
    Challenge a = *this;
    if (m_hints < MAX_PIECES) {
        a.m_hint_list[m_hints] = {pid, orientation, posh, posv};
        ++a.m_hints;
    }
    return a;
}

void Challenge::show()
{
    printf("Pieces = %d: ( ", m_pieces);
    for (int i = 0; i < m_pieces; i++) {
        printf("%d ", m_piece_list[i]);
    }
    printf(")\n");
    printf("Hints = %d:\n", m_hints);
    for (int i = 0; i < m_hints; i++) {
        MoveRec h = m_hint_list[i];
        printf("    pid = %d, orientation = %d, posh = %d, posv = %d\n", h.pid, h.orientation, h.posh, h.posv);
    }
    printf("\n");
}

