//
// game.h
//
#ifndef _GAME_H_
#define _GAME_H_

#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include "table.h"
#include "alt_table.h"

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
    void pb2();
    void pb3();
    void pb4();
    void pb5();

private:
    // Owned by layout
    Table *m_table = nullptr;
    AltTable *m_alt_table = nullptr;
    QPushButton *m_pb1 = nullptr;
    QPushButton *m_pb2 = nullptr;
    QPushButton *m_pb3 = nullptr;
    QPushButton *m_pb4 = nullptr;
    QPushButton *m_pb5 = nullptr;
};

#endif // _GAME_H
