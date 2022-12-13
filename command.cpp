
#include "command.h"

Command::~Command()
{
}

DropPieceCommand::DropPieceCommand(int pix, int orientation, int posh, int posv)
    : m_pix(pix)
    , m_orientation(orientation)
    , m_posh(posh)
    , m_posv(posv)
{

}

DropPieceCommand::~DropPieceCommand()
{
}

bool DropPieceCommand::execute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    return puzzle_book->drop_piece(shape_set, m_pix, m_orientation, m_posh, m_posv);
}

bool DropPieceCommand::unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    (void) shape_set;
    return puzzle_book->lift_piece(m_pix);
}

LiftPieceCommand::LiftPieceCommand(int pix)
    : m_pix(pix)
    , m_orientation(0)
    , m_posh(0)
    , m_posv(0)
{
}

LiftPieceCommand::~LiftPieceCommand()
{
}

bool LiftPieceCommand::execute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    (void) shape_set;
    m_orientation = puzzle_book->orientation(m_pix);
    m_posh = puzzle_book->posh(m_pix);
    m_posv = puzzle_book->posv(m_pix);
    return puzzle_book->lift_piece(m_pix);
}

bool LiftPieceCommand::unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    return puzzle_book->drop_piece(shape_set, m_pix, m_orientation, m_posh, m_posv);
}

NextChallengeCommand::NextChallengeCommand()
{
}

NextChallengeCommand::~NextChallengeCommand()
{
}

bool NextChallengeCommand::execute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    (void) shape_set;
    return puzzle_book->go_to_next_challenge();
}

bool NextChallengeCommand::unexecute(PuzzleBook* puzzle_book, ShapeSet* shape_set)
{
    (void) shape_set;
    return puzzle_book->go_to_previous_challenge();
}


