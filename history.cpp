
#include "history.h"
#include <stdio.h>

#define VERBOSE

History::History()
    : m_max_commands(16384)
    , m_commands(0)
    , m_current(0)
{
    m_command_ptr = new Command*[m_max_commands];
}

History::~History()
{
    for (int i = 0; i < m_commands; i++) {
        delete m_command_ptr[i];
    }
    delete [] m_command_ptr;
}

bool History::can_undo() const
{
    return m_current > 0;
}

bool History::can_redo() const
{
    return m_current < m_commands;
}

void History::execute(Command* c)
{
    if (m_commands >= m_max_commands) {
        double_the_storage();
    }
    for (int i = m_current; i < m_commands; i++) {
        delete m_command_ptr[i];
    }
    m_command_ptr[m_current] = c;
    ++m_current;
    m_commands = m_current;
    c->execute();
}

void History::double_the_storage()
{
    // this will double the value of m_max_items
    // and copy existing data to new array
    // to seamlessly keep the buffer larger than data
    m_max_commands = 2 * m_max_commands;
    Command** temp = new Command*[m_max_commands];
    for (int i = 0; i < m_commands; i++) {
        temp[i] = m_command_ptr[i];
    }
    delete [] m_command_ptr;
    m_command_ptr = temp;
}

void History::undo()
{
    if (can_undo()) {
        --m_current;
        m_command_ptr[m_current]->unexecute();
    }
}

void History::redo()
{
    if (can_redo()) {
        m_command_ptr[m_current]->execute();
        ++m_current;
    }
}
