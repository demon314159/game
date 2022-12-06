
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle_book.h"
#include "full_set.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    PuzzleBook puzzle_book;
    FullSet full_set;
    Hexominos game(puzzle_book, full_set);
    game.show();

    return app.exec();
}
