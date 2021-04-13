
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Game");

    Game game;
    game.show();

    return app.exec();
}
