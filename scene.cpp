//
// scene.cpp
//
#include "scene.h"

Scene::Scene(const ShapeSet* shape_set)
    : m_shape_set(shape_set)
    , m_current_shape(1)
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
    int shape_id = m_current_shape;
    draw_shape(painter, dock(7), shape_id, 0);
    draw_shape(painter, dock(1), shape_id, 1);
    draw_shape(painter, dock(2), shape_id, 2);
    draw_shape(painter, dock(8), shape_id, 3);
    draw_shape(painter, dock(9), shape_id, 4);
    draw_shape(painter, dock(3), shape_id, 5);
    draw_shape(painter, dock(4), shape_id, 6);
    draw_shape(painter, dock(10), shape_id, 7);
}


void Scene::draw_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation)
{
    int maxx = -1000;
    int minx = 1000;
    int maxy = -1000;
    int miny = 1000;
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        maxx = std::max(maxx, m_shape_set->posh(shape_id, i, orientation));
        minx = std::min(minx, m_shape_set->posh(shape_id, i, orientation));
        maxy = std::max(maxy, m_shape_set->posv(shape_id, i, orientation));
        miny = std::min(miny, m_shape_set->posv(shape_id, i, orientation));
    }
    int cx = m_unit * (maxx + minx) / 2;
    int cy = m_unit * (maxy + miny) / 2;
    for (int i = 0; i < m_shape_set->tiles(shape_id); i++) {
        int x1 = rect.center().x() + m_shape_set->posh(shape_id, i, orientation) * m_unit - cx;
        int y1 = rect.center().y() - m_shape_set->posv(shape_id, i, orientation) * m_unit + cy;
        painter.drawRect(QRect(x1 - m_unit/2, y1-m_unit/2, m_unit - 1, m_unit - 1));
    }
}

void Scene::next_shape()
{
    if ((m_current_shape + 1) < MAX_SHAPES) {
        ++m_current_shape;
    }
}

void Scene::prev_shape()
{
    if (m_current_shape > 1) {
        --m_current_shape;
    }
}
