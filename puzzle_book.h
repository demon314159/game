//
// puzzle_book.h
//
#if !defined(_PUZZLE_BOOK_H_)
#define _PUZZLE_BOOK_H_

#define MAX_CHALLENGES 48

#include "challenge.h"

class PuzzleBook
{
public:
    PuzzleBook(void);
    ~PuzzleBook();
    void add(const Challenge& challenge);

protected:
    int m_challenges;
    Challenge m_list[MAX_CHALLENGES];
};

#endif // _PUZZLE_BOOK_H_
