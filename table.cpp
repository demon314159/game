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
        m_scene.mouse_left_press(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
    }
    update();
    QWidget::mousePressEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_scene.mouse_left_release(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
    }
    update();
    QWidget::mouseReleaseEvent(e);
}

void Table::mouseMoveEvent(QMouseEvent* e)
{
    m_scene.mouse_move(e->pos().x(), e->pos().y());
    update();
    QWidget::mouseMoveEvent(e);
}

void Table::wheelEvent(QWheelEvent* e)
{
    int angle = e->angleDelta().y();
    m_scene.mouse_wheel(e->pos().x(), e->pos().y(), angle > 0);
    update();
    e->accept();
}

