
#ifndef _HISTORY_H_
#define _HISTORY_H_

#include "command.h"
#include "puzzle_book.h"
#include "shape_set.h"

class History
{
public:
    History(PuzzleBook* puzzle_book, ShapeSet* shape_set);
    ~History();
    void do_command(Command* c);
    void undo_command();
    void redo_command();
    bool end_of_undo() const;
    bool end_of_redo() const;

private:
    PuzzleBook* m_puzzle_book;
    ShapeSet* m_shape_set;
    int m_max_commands;
    int m_commands;
    int m_current;
    Command** m_command_ptr;
    void double_the_storage();
};

#endif // _HISTORY_H_
