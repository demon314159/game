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

void Scene::draw(QPainter& painter, int x_base, int y_base, int width, int height)
{

    painter.setPen(Qt::red);
    painter.drawRect(QRect(x_base, y_base, width - 1, height - 1));
}
