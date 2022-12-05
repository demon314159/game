
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle.h"
#include "full_set.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    Puzzle puzzle;
    FullSet full_set;
    Hexominos game(puzzle, full_set);
    game.show();

    return app.exec();
}
