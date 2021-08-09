//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(int& view_ix, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_tilt(0.0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_thingy(NULL)
    , m_view_ix(view_ix)
    , m_mvp_matrix(mvp_matrix)
    , m_rot_matrix(rot_matrix)
{
    if (m_view_ix == 1) {
        m_tilt = 90.0;
        setMinimumWidth(337);
        setMinimumHeight(600);
    } else {
        m_tilt = 35.0;
        setMinimumWidth(600);
        setMinimumHeight(337);
    }
}

Table::~Table()
{
    makeCurrent();
    delete m_thingy;
    doneCurrent();
}

void Table::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus(m_tilt);
    timer.start(100, this);
}

void Table::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 2.5, zFar = 15.0, fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void Table::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_view_ix == 0) {
        QVector3D my_axis = {1.0, 0.0, 0.0};
        QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, m_tilt);
        QMatrix4x4 matrix;
        matrix.translate(0.0, -0.25, -6.0);
        matrix.rotate(my_rot);
        // Set modelview-projection matrix
        m_mvp_matrix = m_projection * matrix;
        m_rot_matrix = matrix;
        m_program.setUniformValue("mvp_matrix", m_projection * matrix);
        m_program.setUniformValue("rot_matrix", matrix);
    } else { // m_viewIx == 1
        QVector3D my_axis = {1.0, 0.0, 0.0};
        QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, m_tilt);
        QMatrix4x4 matrix;
        matrix.translate(0.0, -3.00, -13.0);
        matrix.rotate(my_rot);
        // Set modelview-projection matrix
        m_mvp_matrix = m_projection * matrix;
        m_rot_matrix = matrix;
        m_program.setUniformValue("mvp_matrix", m_projection * matrix);
        m_program.setUniformValue("rot_matrix", matrix);
    }

    // Draw cube geometry
    m_thingy->drawCubeGeometry(&m_program);
}

void Table::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    if (!m_program.link())
        close();
    if (!m_program.bind())
        close();
}

void Table::timerEvent(QTimerEvent *)
{
    if (isVisible()) {
    }
}

