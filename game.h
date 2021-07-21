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
#include <QLabel>
#include <QWidget>
#include "table.h"
#include "alt_table.h"
#include "image_set.h"
#include "high_score.h"

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
    HighScore m_high_score;
    int m_view_ix;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    ImageSet m_image_set;
    Table* m_table = nullptr;
    AltTable* m_alt_table = nullptr;
    QStackedWidget* m_stacked_widget = nullptr;
    QPushButton* m_pb1 = nullptr;
    QLabel* m_label = nullptr;
};

#endif // _GAME_H
