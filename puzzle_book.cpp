//
// puzzle_book.cpp
//
#include "puzzle_book.h"
#include <stdio.h>
#include <sys/stat.h>

PuzzleBook::PuzzleBook(const char* name)
    : m_challenges(0)
    , m_current_challenge(0)
{
    FILE* ffi = fopen(name, "r");
    if (ffi == NULL) {
        add_challenges();
        return;
    }
    if (1 != fread(this, sizeof(PuzzleBook), 1, ffi) ) {
        add_challenges();
    }
    fclose(ffi);
}

PuzzleBook::~PuzzleBook()
{
}

void PuzzleBook::add_challenges()
{
    add_challenge(Challenge(8, 6).p(4, 0, 0, 0).p(5).p(7).p(11).p(13, 5, 4, 2).p(14).p(14).p(28));
    add_challenge(Challenge(8, 6).p(3).p(8).p(12, 0, 5, 4).p(17).p(23).p(25).p(28, 4, 7, 0).p(31));
    add_challenge(Challenge(8, 6).p(3).p(6).p(7).p(8, 4, 7, 2).p(11, 2, 4, 3).p(13).p(25).p(26));
    add_challenge(Challenge(8, 6).p(2, 0, 0, 1).p(4).p(8).p(8).p(15).p(16).p(22).p(31, 6, 6, 2));
}

void PuzzleBook::add_challenge(const Challenge& challenge)
{
    if (m_challenges < MAX_CHALLENGES) {
        m_list[m_challenges] = challenge;
        ++m_challenges;
    }
}

void PuzzleBook::save(const char* name)
{
    FILE* ffo = fopen(name, "w");
    if (ffo == NULL)
        return;
    fwrite(this, sizeof(PuzzleBook), 1, ffo);
    fclose(ffo);
}

bool PuzzleBook::puzzle_solved() const
{
    return ((m_current_challenge == (m_challenges + 1)) && current_challenge_solved());
}

bool PuzzleBook::current_challenge_solved() const
{
    return (m_list[m_current_challenge].solved());
}

int PuzzleBook::challenges() const
{
    return m_challenges;
}

int PuzzleBook::current_challenge() const
{
    return m_current_challenge;
}

bool PuzzleBook::go_to_next_challenge()
{
    if ((m_current_challenge + 1) >= m_challenges)
        return false;
    if (!m_list[m_current_challenge].solved())
        return false;
    ++m_current_challenge;
    return true;
}

bool PuzzleBook::go_to_previous_challenge()
{
    if (m_current_challenge < 1)
        return false;
    --m_current_challenge;
    return true;
}

bool PuzzleBook::add_piece(int pix, int orientation, int posh, int posv)
{
    Challenge* ch = m_list + m_current_challenge;
    if (pix >= ch->pieces())
        return false;

//... left off here, draw it out to find borders
}

bool PuzzleBook::remove_piece(int pix)
{
}


