
#include <QtWidgets>

#include "step1.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Step1");

    Step1 game;
    game.show();

    int res = app.exec();
    return res;
}
