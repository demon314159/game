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
    bool puzzle_solved() const;
    bool current_challenge_solved() const;
    int challenges() const;
    int current_challenge() const;
    bool go_to_next_challenge();
    bool go_to_previous_challenge();
    bool add_piece(int pix, int orientation, int posh, int posv);
    bool remove_piece(int pix);

protected:
    int m_challenges;
    int m_current_challenge;
    Challenge m_list[MAX_CHALLENGES];

    void add_challenges();
    void add_challenge(const Challenge& challenge);
};

#endif // _PUZZLE_BOOK_H_
