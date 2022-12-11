//
// challenge.cpp
//

#include "challenge.h"

#include "stdio.h"

Challenge::Challenge(void)
    : m_dimh(0)
    , m_dimv(0)
    , m_pieces(0)
{
    printf("Challenge::Challenge()\n");
}

Challenge::Challenge(int dimh, int dimv)
    : m_dimh(dimh)
    , m_dimv(dimv)
    , m_pieces(0)
{
    printf("Challenge::Challenge(%d, %d)\n", dimh, dimv);
}

Challenge::~Challenge()
{
    if (m_pieces == 0) {
        printf("Challenge::~Challenge(): no pieces\n");
    } else {
        printf("Challenge::~Challenge(): %d pieces:", m_pieces);
            for (int i = 0; i < m_pieces; i++) {
                printf("%d ", m_piece_list[i].shape_id());
            }
        printf("\n");
    }
}

Challenge& Challenge::p(int shape_id)
{
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        m_piece_list[m_pieces] = Piece(shape_id, false, false, 0, 0, 0);
        ++m_pieces;
    }
    return *this;
}

Challenge& Challenge::p(int shape_id, int orientation, int posh, int posv)
{
    if (m_pieces < MAX_CHALLENGE_PIECES) {
        m_piece_list[m_pieces] = Piece(shape_id, true, true, orientation, posh, posv);
        ++m_pieces;
    }
    return *this;
}

int Challenge::pieces() const
{
    return m_pieces;
}

bool Challenge::solved() const
{
    for (int i = 0; i < m_pieces; i++) {
        if (!m_piece_list[i].on_board())
            return false;
    }
    return true;
}

Piece Challenge::get_piece(int pix) const
{
    return m_piece_list[pix];
}

