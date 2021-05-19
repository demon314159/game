//
// table.cpp
//
#include "table.h"

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Table::~Table()
{
}

void Table::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Table::resizeGL(int w, int h)
{
//    m_projection.setToIdentity();
//    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void Table::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);
}



