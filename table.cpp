//
// table.cpp
//
#include "table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

Table::Table(PuzzleBook* puzzle_book, const ShapeSet* shape_set, QWidget *parent)
    : QWidget(parent)
    , m_scene(puzzle_book, shape_set)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(480);
    setMinimumWidth(640);
}

int Table::text_width(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.width();
}

int Table::text_height(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.height();
}

void Table::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);
//    int th = text_height(painter, QString("0"));

    m_scene.draw(painter);
}

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        printf("Left Button press (%d, %d)\n", e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
        printf("Right Button press\n");
    }
    QWidget::mousePressEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        printf("Left Button release\n");
    } else if (e->button() == Qt::RightButton) {
        printf("Right Button release\n");
    }
    QWidget::mouseReleaseEvent(e);
}

