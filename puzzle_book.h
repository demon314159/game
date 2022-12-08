//
// puzzle_book.h
//
#if !defined(_PUZZLE_BOOK_H_)
#define _PUZZLE_BOOK_H_

#define MAX_CHALLENGES 48
#define PUZZLE_BOOK_FILE_NAME ".hexominoes.dat"

#include "challenge.h"

class PuzzleBook
{
public:
    PuzzleBook(const char* name);
    ~PuzzleBook();
    void save(const char* name);

protected:
    int m_challenges;
    Challenge m_list[MAX_CHALLENGES];

    void add_challenges();
    void add(const Challenge& challenge);
};

#endif // _PUZZLE_BOOK_H_
