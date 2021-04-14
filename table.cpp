//
// table.cpp
//
#include "table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

Table::Table(QWidget *parent)
    : QWidget(parent)
    , m_puck(10.0, 10.0)
    , m_x_base(0)
    , m_y_base(0)
    , m_width(100)
    , m_height(100)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(162);
    setMinimumWidth(512);
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

    painter.setPen(Qt::black);

    m_width = painter.viewport().width();
    m_height = painter.viewport().height();
    m_x_base = painter.viewport().left();
    m_y_base = painter.viewport().top();

    painter.setPen(Qt::black);
    painter.drawRect(QRect(m_x_base,
                           m_y_base,
                           m_width - 1,
                           m_height - 1));
}


