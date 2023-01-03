//
// puzzle_book.cpp
//
#include "puzzle_book.h"
#include "stdio.h"
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

    add_challenge(Challenge(8, 6).p(4, 0, 0, 0).p(5).p(7).p(11).p(13, 5, 4, 2).p(14).p(14).p(28)); // 1
    add_challenge(Challenge(8, 6).p(3).p(8).p(12, 1, 5, 5).p(17).p(23).p(25).p(28, 4, 7, 0).p(31)); // 2
    add_challenge(Challenge(8, 6).p(3).p(6).p(7).p(8, 4, 7, 2).p(11, 2, 4, 3).p(13).p(25).p(26)); // 3
    add_challenge(Challenge(8, 6).p(2, 0, 0, 1).p(4).p(8).p(8).p(15).p(16).p(22).p(31, 6, 6, 2)); // 4
    add_challenge(Challenge(8, 6).p(3).p(10).p(11, 1, 4, 5).p(13).p(14).p(17).p(26).p(31, 0, 1, 3)); // 5
    add_challenge(Challenge(8, 6).p(7).p(8, 2, 7, 3).p(8).p(12).p(15).p(17, 7, 3, 5).p(18).p(21)); // 6
    add_challenge(Challenge(8, 6).p(2, 4, 7, 1).p(5).p(14).p(14).p(20).p(21).p(26, 1, 0, 5).p(28)); // 7
    add_challenge(Challenge(8, 6).p(4, 4, 7, 1).p(6).p(8).p(11).p(12).p(21).p(23, 1, 3, 5).p(28)); // 8
    add_challenge(Challenge(8, 6).p(2).p(10).p(16).p(20).p(21).p(26).p(31).p(34, 0, 4, 0)); // 9
    add_challenge(Challenge(8, 6).p(2).p(15).p(21).p(23).p(26).p(28, 1, 4, 5).p(32).p(35)); // 10
    add_challenge(Challenge(8, 6).p(3).p(11).p(12).p(15).p(20).p(22, 0, 3, 1).p(26).p(28)); // 11
    add_challenge(Challenge(8, 6).p(2).p(3).p(7).p(15).p(16, 1, 3, 2).p(21).p(22).p(30)); // 12
    add_challenge(Challenge(8, 6).p(11).p(14).p(15).p(16).p(17).p(24, 3, 5, 3).p(26).p(33)); // 13
    add_challenge(Challenge(8, 6).p(4).p(8).p(12, 1, 2, 4).p(19).p(22).p(28).p(30).p(31)); // 14
    add_challenge(Challenge(8, 6).p(2).p(5).p(8).p(12).p(18).p(21).p(30).p(31)); // 15
    add_challenge(Challenge(8, 6).p(2).p(7).p(12).p(14).p(14).p(26).p(31).p(35)); // 16



// add these in at the end
//    add_challenge(Challenge(10, 6).p(3).p(11).p(20).p(22).p(25).p(25).p(26).p(28).p(31).p(32)); // 47
//    add_challenge(Challenge(10, 6).p(23).p(5).p(12).p(21).p(1).p(25).p(26).p(28).p(32).p(33)); // 48

// temporarily force challenge to last one so it wan be built easily
    m_current_challenge = m_challenges - 1;

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
    return ((m_current_challenge == (m_challenges - 1)) && current_challenge_solved());
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
//    if (!m_list[m_current_challenge].solved())
//        return false;
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

int PuzzleBook::pieces() const
{
    return m_list[m_current_challenge].pieces();
}

int PuzzleBook::shape_id(int pix) const
{
    return m_list[m_current_challenge].shape_id(pix);
}

bool PuzzleBook::locked(int pix) const
{
    return m_list[m_current_challenge].locked(pix);
}

bool PuzzleBook::on_board(int pix) const
{
    return m_list[m_current_challenge].on_board(pix);
}

int PuzzleBook::orientation(int pix) const
{
    return m_list[m_current_challenge].orientation(pix);
}

int PuzzleBook::posh(int pix) const
{
    return m_list[m_current_challenge].posh(pix);
}

int PuzzleBook::posv(int pix) const
{
    return m_list[m_current_challenge].posv(pix);
}

bool PuzzleBook::drop_piece(const ShapeSet* shape_set, int pix, int orientation, int posh, int posv)
{
    return m_list[m_current_challenge].drop_piece(shape_set, pix, orientation, posh, posv);
}

bool PuzzleBook::lift_piece(int pix)
{
    return m_list[m_current_challenge].lift_piece(pix);
}

int PuzzleBook::dimh() const
{
    return m_list[m_current_challenge].dimh();
}

int PuzzleBook::dimv() const
{
    return m_list[m_current_challenge].dimv();
}

void PuzzleBook::set_orientation(int pix, int orientation)
{
    m_list[m_current_challenge].set_orientation(pix, orientation);
}
