
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle.h"
#include "fullset.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    Puzzle puzzle;
    FullSet fullset;
    Hexominos game(puzzle, fullset);
    game.show();

    return app.exec();
}
