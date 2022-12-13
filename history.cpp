
#include "history.h"
#include <stdio.h>

History::History(PuzzleBook* puzzle_book, ShapeSet* shape_set)
    : m_puzzle_book(puzzle_book)
    , m_shape_set(shape_set)
    , m_max_commands(16384)
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

void History::do_command(Command* c)
{
    if (m_commands >= m_max_commands) {
        double_the_storage();
    }
    for (int i = m_current; i < m_commands; i++) {
        delete m_command_ptr[i];
    }

    if (c->execute(m_puzzle_book, m_shape_set)) {
        m_command_ptr[m_current] = c;
        ++m_current;
        m_commands = m_current;
    }
}

void History::undo_command()
{
    if (!end_of_undo()) {
        --m_current;
        m_command_ptr[m_current]->unexecute(m_puzzle_book, m_shape_set);
    }
}

void History::redo_command()
{
    if (!end_of_redo()) {
        m_command_ptr[m_current]->execute(m_puzzle_book, m_shape_set);
        ++m_current;
    }
}

bool History::end_of_undo() const
{
    return m_current == 0;
}

bool History::end_of_redo() const
{
    return m_current == m_commands;
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

