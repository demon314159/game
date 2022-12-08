
//
// moverec.h
//
// When a piece is on_board, the fields orientation, posh and posv define its position.
// When a piece is a hint, it cannot be changed, it will also be on_board.
// A regular move made by the player will be on_board and not a hint, and may even be
// an invalid move.
//
//
#ifndef _MOVEREC_H_
#define _MOVEREC_H_

struct MoveRec {
    int pid;
    bool hint;
    bool on_board;
    int orientation;
    int posh;
    int posv;
};

#endif // _MOVEREC_H_
