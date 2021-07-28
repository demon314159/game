
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
    printf("\n  There are three ways to experience this game:\n");
    printf("\n  'arcade-baseball' or 'arcade-baseball 0' launches a 580 x 994 Top View\n");
    printf("\n  'arcade-baseball 1' launches a 1902 x 994 Perspective View\n");
    printf("\n  'arcade-baseball 2' launches a 1062 x 1834 Top View for monitor in portrait mode\n");
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
    game.show();

    return app.exec();
}
