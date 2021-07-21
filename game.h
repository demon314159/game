//
// game.h
//
#ifndef _GAME_H_
#define _GAME_H_

#include <QStackedWidget>
#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include "table.h"
#include "alt_table.h"
#include "image_set.h"

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
    void pb2();
    void pb3();
    void pb4();
    void pb5();

private:
    // Owned by layout
    int m_view_ix;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    ImageSet m_image_set;
    Table* m_table = nullptr;
    AltTable* m_alt_table = nullptr;
    QStackedWidget* m_stacked_widget = nullptr;
    QPushButton* m_pb1 = nullptr;
    QPushButton* m_pb2 = nullptr;
    QPushButton* m_pb3 = nullptr;
    QPushButton* m_pb4 = nullptr;
    QPushButton* m_pb5 = nullptr;
};

#endif // _GAME_H
