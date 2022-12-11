
#include "command.h"

Command::~Command()
{
}

DropPieceCommand::DropPieceCommand(int pix, int orientation, int posh, int posv)
    : m_pix(pix)
{
}

DropPieceCommand::~DropPieceCommand()
{
}

void DropPieceCommand::execute()
{
}

void DropPieceCommand::unexecute()
{
}

LiftPieceCommand::LiftPieceCommand(int pix)
    : m_pix(pix)
{
}

LiftPieceCommand::~LiftPieceCommand()
{
}

void LiftPieceCommand::execute()
{
}

void LiftPieceCommand::unexecute()
{
}

NextChallengeCommand::NextChallengeCommand()
{
}

NextChallengeCommand::~NextChallengeCommand()
{
}

void NextChallengeCommand::execute()
{
}

void NextChallengeCommand::unexecute()
{
}


