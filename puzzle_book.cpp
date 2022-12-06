//
// puzzle_book.cpp
//
#include "puzzle_book.h"

PuzzleBook::PuzzleBook(void)
    : m_challenges(0)
{
    add(Challenge(8, 6).p(4, 0, 0, 0).p(5).p(7).p(11).p(13, 5, 4, 2).p(14).p(14).p(28));
    add(Challenge(8, 6).p(3).p(8).p(12, 0, 5, 4).p(17).p(23).p(25).p(28, 4, 7, 0).p(31));
    add(Challenge(8, 6).p(3).p(6).p(7).p(8, 4, 7, 2).p(11, 2, 4, 3).p(13).p(25).p(26));
    add(Challenge(8, 6).p(2, 0, 0, 1).p(4).p(8).p(8).p(15).p(16).p(22).p(31, 6, 6, 2));
}

PuzzleBook::~PuzzleBook()
{
    for (int i = 0; i < m_challenges; i++) {
        delete m_list[i];
    }
}

void PuzzleBook::add(const Challenge& challenge)
{
    if (m_challenges < MAX_CHALLENGES) {
        m_list[m_challenges] = new Challenge(challenge);
        ++m_challenges;
    }
}


