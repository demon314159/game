//
// puzzle.h
//
#if !defined(_PUZZLE_H_)
#define _PUZZLE_H_

#define MAX_CHALLENGES 100

#include "challenge.h"

class Puzzle
{
public:
    Puzzle(void);
    ~Puzzle();
    void add(const Challenge& challenge);

protected:
    int m_challenges;
    Challenge* m_list[MAX_CHALLENGES];
};

#endif // _PUZZLE_H_
