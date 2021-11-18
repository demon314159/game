
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Bricks");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Game game(1);
    game.showMaximized();

    return app.exec();
}
