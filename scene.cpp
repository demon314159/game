//
// scene.cpp
//
#include "scene.h"

#include <stdio.h>

Scene::Scene()
{
    printf("Scene::Scene()\n");
}

Scene::~Scene()
{
    printf("Scene::~Scene()\n");
}

void Scene::determine_size(QPainter& painter)
{
    int vx = painter.viewport().left();
    int vy = painter.viewport().top();
    int vw = painter.viewport().width();
    int vh = painter.viewport().height();
    printf("determine_size %d, %d, %d, %d\n", vx, vy, vw, vh);
    int xgy = (vh * 4) / 3;
    int ygx = (vw * 3) / 4;
    printf("    xgy = %d, ygx = %d\n", xgy, ygx);
    if (xgy <= vw) {
        m_xbase = vx + (vw - xgy) / 2;
        m_ybase = vy;
        m_unit = vh / VERT_UNITS;
        printf("    case 1: m_unit = %d, total h = %d, total v = %d\n", m_unit, m_unit * HORZ_UNITS, m_unit * VERT_UNITS);
    } else {
        m_xbase = vx;
        m_ybase = vy + (vh - ygx) / 2;
        m_unit = vw / HORZ_UNITS;
        printf("    case i2: m_unit = %d, total h = %d, total v = %d\n", m_unit, m_unit * HORZ_UNITS, m_unit * VERT_UNITS);
    }
}

void Scene::draw(QPainter& painter)
{
    determine_size(painter);

    painter.setPen(Qt::red);
    painter.drawRect(QRect(m_xbase, m_ybase, m_unit * HORZ_UNITS - 1, m_unit * VERT_UNITS - 1));
}
