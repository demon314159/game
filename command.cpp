
#include "command.h"
#include <stdio.h>

Command::~Command()
{
}

AddBrickCommand::AddBrickCommand(const QString& msg)
    : m_msg(msg)
{
}

void AddBrickCommand::execute()
{
    printf("Execute '%s'\n", m_msg.toLatin1().data());
}

void AddBrickCommand::unexecute()
{
    printf("Unexecute '%s'\n", m_msg.toLatin1().data());
}

AddBrickCommand::~AddBrickCommand()
{
    printf("Destroy '%s'\n", m_msg.toLatin1().data());
}
