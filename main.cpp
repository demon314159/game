
#include <QtWidgets>

#include "hexominos.h"
#include "challenge.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    Challenge c1 = Challenge(8, 6).p(4).p(5).p(7).p(11).p(13).p(14).p(14).p(28).h(13, 5, 4, 2).h(4, 0, 0, 0);
    c1.show();

    Hexominos game;
    game.show();

    return app.exec();
}
