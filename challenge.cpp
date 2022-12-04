//
// challenge.cpp
//
#include "challenge.h"

Challenge::Challenge(int dimh, int dimv)
    : m_dimh(dimh)
    , m_dimv(dimv)
    , m_pieces(0)
    , m_hints(0)
{
}

Challenge::~Challenge()
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

Challenge Challenge::p(int pid, int orientation, int posh, int posv)
{
    Challenge a = *this;
    if (m_pieces < MAX_PIECES) {
        a.m_piece_list[m_pieces] = pid;
        ++a.m_pieces;
        if (m_hints < MAX_PIECES) {
            a.m_hint_list[m_hints] = {pid, orientation, posh, posv};
            ++a.m_hints;
        }
    }
    return a;
}
