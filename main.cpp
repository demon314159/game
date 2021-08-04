
#include <QtWidgets>

#include "game.h"

int main(int argv, char **args)
{
    int view_ix = 0;
    if (argv > 1) {
        view_ix = atoi(args[1]);
    }
    QApplication app(argv, args);
    app.setApplicationName("Arcade Baseball");

    printf("\nArcade Baseball\n\n");
    printf("\n  There are two ways to experience this game:\n");
    printf("\n  'arcade-baseball' launches a Perspective View in Landscape format\n");
    printf("\n  'arcade-baseball 1' launches a Top View in Portrait format\n");
    printf("\n");
    printf("\n  Left mouse button or left shift key pitches the Ball\n");
    printf("\n  Right mouse button or right shift key activates the Bat\n");
    printf("\n  Game Over after three Outs\n");
    printf("\n  (Hitting all targets will cancel an Out)\n");
    printf("\n  The N key will start a new game\n\n");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Game game(view_ix);
    game.showMaximized();

    return app.exec();
}
