//
// table.cpp
//
#include "table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

Table::Table(const ShapeSet* shape_set, QWidget *parent)
    : QWidget(parent)
    , m_scene(shape_set)
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

void Table::next_shape()
{
    m_scene.next_shape();
    update();
}

void Table::prev_shape()
{
    m_scene.prev_shape();
    update();
}

