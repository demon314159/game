
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    int view_ix = 0;
    if (argv > 1) {
        view_ix = atoi(args[1]);
    }
    QApplication app(argv, args);
    app.setApplicationName("Bricks");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Game game(view_ix);
    game.showMaximized();

    return app.exec();
}
