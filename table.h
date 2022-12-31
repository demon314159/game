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

#include "scene.h"
#include "shape_set.h"
#include "puzzle_book.h"

class Table: public QWidget
{
    Q_OBJECT

public:
    explicit Table(PuzzleBook* puzzle_book, const ShapeSet* shape_set, QWidget *parent = nullptr);

protected:
    int text_width(QPainter& painter, const QString &s);
    int text_height(QPainter& painter, const QString &s);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    Scene m_scene;
};

#endif // _TABLE_H_
