
#ifndef _COMMAND_H_
#define _COMMAND_H

#include "puzzle_book.h"
#include "shape_set.h"

class Command
{
public:
    virtual ~Command();
    virtual bool execute(PuzzleBook* puzzle_book, ShapeSet* shape_set) = 0;
    virtual bool unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set) = 0;
};

class DropPieceCommand: public Command
{
public:
    DropPieceCommand(int pix, int orientation, int posh, int posv);
    ~DropPieceCommand();
    bool execute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
    bool unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
private:
    int m_pix;
    int m_orientation;
    int m_posh;
    int m_posv;
};

class LiftPieceCommand: public Command
{
public:
    LiftPieceCommand(int pix);
    ~LiftPieceCommand();
    bool execute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
    bool unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
private:
    int m_pix;
    int m_orientation;
    int m_posh;
    int m_posv;
};

class PreviousChallengeCommand: public Command
{
public:
    PreviousChallengeCommand();
    ~PreviousChallengeCommand();
    bool execute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
    bool unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
private:
};

class NextChallengeCommand: public Command
{
public:
    NextChallengeCommand();
    ~NextChallengeCommand();
    bool execute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
    bool unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set) override;
private:
};

#endif // _COMMAND_H_
