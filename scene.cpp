//
// scene.cpp
//
#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::determine_layout(QPainter& painter)
{
    int vx = painter.viewport().left();
    int vy = painter.viewport().top();
    int vw = painter.viewport().width();
    int vh = painter.viewport().height();
    int xgy = (vh * 4) / 3;
    int ygx = (vw * 3) / 4;
    if (xgy <= vw) {
        m_xbase = vx + (vw - xgy) / 2;
        m_ybase = vy;
        m_unit = vh / VERT_UNITS;
    } else {
        m_xbase = vx;
        m_ybase = vy + (vh - ygx) / 2;
        m_unit = vw / HORZ_UNITS;
    }
}

QRect Scene::dock(int dix) const
{
    switch(dix) {
        case 1:
            return QRect(m_xbase + 6 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 2:
            return QRect(m_xbase + 12 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 3:
            return QRect(m_xbase + 6 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 4:
            return QRect(m_xbase + 12 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 5:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 6 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 6:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 6 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 7:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 8:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 0 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 9:
            return QRect(m_xbase + 0 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);
        case 10:
            return QRect(m_xbase + 18 * m_unit, m_ybase + 12 * m_unit, 6 * m_unit - 1, 6 * m_unit - 1);

        default:
            return QRect(m_xbase + 7 * m_unit, m_ybase + 6 * m_unit, 10 * m_unit - 1, 6 * m_unit - 1);
    }
}

void Scene::draw(QPainter& painter)
{
    determine_layout(painter);

    painter.setPen(Qt::red);
    painter.drawRect(QRect(m_xbase, m_ybase, m_unit * HORZ_UNITS - 1, m_unit * VERT_UNITS - 1));
    painter.setPen(Qt::black);
    painter.drawRect(dock(0));
    painter.drawRect(dock(1));
    painter.drawRect(dock(2));
    painter.drawRect(dock(3));
    painter.drawRect(dock(4));
    painter.drawRect(dock(5));
    painter.drawRect(dock(6));
    painter.drawRect(dock(7));
    painter.drawRect(dock(8));
    painter.drawRect(dock(9));
    painter.drawRect(dock(10));
}
