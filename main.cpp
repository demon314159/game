
#include <QtWidgets>

#include "game.h"
#include "look.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Bricks");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Look::set_3d(false);

    Game game;
    game.showMaximized();

    return app.exec();
}
