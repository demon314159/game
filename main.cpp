
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Game");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//    format.setVersion(3, 2);
//    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Game game;
    game.show();

    return app.exec();
}
