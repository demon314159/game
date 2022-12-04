//
// puzzle.cpp
//
#include "puzzle.h"

Puzzle::Puzzle(void)
    : m_challenges(0)
{
}

Puzzle::~Puzzle()
{
    for (int i = 0; i < m_challenges; i++) {
        delete m_list[i];
    }
}

void Puzzle::add(const Challenge& challenge)
{
    if (m_challenges < MAX_CHALLENGES) {
        m_list[m_challenges] = new Challenge(challenge);
        ++m_challenges;
    }
}


