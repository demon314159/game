
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    int view_ix = 0;
    if (argv > 1) {
        view_ix = atoi(args[1]);
    }
    printf("view_ix = %d\n", view_ix);
    QApplication app(argv, args);
    app.setApplicationName("Game");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//    format.setVersion(3, 2);
//    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Game game(view_ix);
    game.show();

    return app.exec();
}
