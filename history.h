
#ifndef _HISTORY_H_
#define _HISTORY_H_

#include "command.h"

class History
{
public:
    History();
    ~History();
    bool can_undo() const;
    bool can_redo() const;
    void execute(Command* c);
    void undo();
    void redo();

private:
    int m_max_commands;
    int m_commands;
    int m_current;
    Command** m_command_ptr;
    void double_the_storage();
};

#endif // _HISTORY_H_
