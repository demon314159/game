
#include <QtWidgets>

#include "hexominos.h"
#include "challenge.h"
#include "puzzle.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    Puzzle puzzle;

    puzzle.add(Challenge(8, 6).p(4, 0, 0, 0).p(5).p(7).p(11).p(13, 5, 4, 2).p(14).p(14).p(28));
    puzzle.add(Challenge(8, 6).p(3).p(8).p(12, 0, 5, 4).p(17).p(23).p(25).p(28, 4, 7, 0).p(31));
    puzzle.add(Challenge(8, 6).p(3).p(6).p(7).p(8, 4, 7, 2).p(11, 2, 4, 3).p(13).p(25).p(26));
    puzzle.add(Challenge(8, 6).p(2, 0, 0, 1).p(4).p(8).p(8).p(15).p(16).p(22).p(31, 6, 6, 2));

    Hexominos game(puzzle);
    game.show();

    return app.exec();
}
