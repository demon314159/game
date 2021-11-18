//
// game.h
//
#if !defined(_GAME_H_)
#define _GAME_H_

#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include "table.h"

class Game: public QMainWindow
{
    Q_OBJECT

public:
    Game();
    ~Game();

private:
    void initializeWindow();

private slots:
    void pb1();

private:
    Table* m_table = nullptr;
    QPushButton* m_pb1 = nullptr;
};

#endif // _GAME_H_
