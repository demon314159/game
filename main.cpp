
#include <QtWidgets>

#include "game.h"
#include "look.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Race");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    Game game;
    game.showMaximized();

    return app.exec();
}
