
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle_book.h"
#include "full_set.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    FullSet* full_set = new(FullSet);
    PuzzleBook* puzzle_book = new(PuzzleBook);
    PuzzleBook* work_book = new(PuzzleBook);
    Hexominos game(full_set, puzzle_book, work_book);
    game.show();

    int res = app.exec();
    delete(work_book);
    delete(puzzle_book);
    delete(full_set);
    return res;
}
