//
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPushButton>

#include "scene.h"
#include "shape_set.h"
#include "puzzle_book.h"

class Table: public QWidget
{
    Q_OBJECT

public:
    explicit Table(PuzzleBook* puzzle_book, const ShapeSet* shape_set, QPushButton* previous_button, QPushButton* next_button, QWidget *parent);
    void pb_next_challenge();
    void pb_previous_challenge();
    void clear_board();

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void full_update();


private:
    QWidget* m_parent;
    QPushButton* m_previous_button;
    QPushButton* m_next_button;
    PuzzleBook* m_puzzle_book;
    Scene m_scene;
};

#endif // _TABLE_H_
