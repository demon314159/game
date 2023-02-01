
#include <QtWidgets>

#include "game.h"
#include "look.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("OpenGL Baseline");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    Look::process_options(argv, args);
    Game game;
    game.showMaximized();

    return app.exec();
}
