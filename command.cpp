
#include "command.h"

Command::~Command()
{
}

AddPieceCommand::AddPieceCommand(int pix, int orientation, int posh, int posv)
    : m_pix(pix)
{
}

AddPieceCommand::~AddPieceCommand()
{
}

void AddPieceCommand::execute()
{
}

void AddPieceCommand::unexecute()
{
}

RemovePieceCommand::RemovePieceCommand(int pix)
    : m_pix(pix)
{
}

RemovePieceCommand::~RemovePieceCommand()
{
}

void RemovePieceCommand::execute()
{
}

void RemovePieceCommand::unexecute()
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


