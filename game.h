//
// game.h
//
#ifndef _GAME_H_
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
    Game(int view_ix);
    ~Game();

private:
    void initializeWindow();

private slots:
    void pb1();

private:
    // Owned by layout
    int m_view_ix;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    Table* m_table = nullptr;
    QPushButton* m_pb1 = nullptr;
};

#endif // _GAME_H
