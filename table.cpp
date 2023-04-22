//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(int& view_ix, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_time_at_start(high_resolution_clock::now())
    , m_xrot(0.0)
    , m_yrot(0.0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_timer(new QTimer(this))
    , m_thingy(NULL)
    , m_view_ix(view_ix)
    , m_mvp_matrix(mvp_matrix)
    , m_rot_matrix(rot_matrix)
{
    m_xrot = 0.0;
    setMinimumWidth(600);
    setMinimumHeight(337);
    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Table::update));
    m_timer->start(33);
}

Table::~Table()
{
    m_timer->stop();
    delete m_timer;
    makeCurrent();
    delete m_thingy;
    doneCurrent();
}

void Table::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus();
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
    float turns_per_second = 3.0 / 20.0;

    high_resolution_clock::time_point time_in = high_resolution_clock::now();
    high_resolution_clock::duration total_period = time_in - m_time_at_start;
    m_time_at_start = time_in;
    int tp = duration_cast<nanoseconds>(total_period).count();
    m_qa.add_sample(tp);

    m_yrot += ((360.0 * turns_per_second / 1000000000.0) * (double) tp);

    QVector3D axis_y = {0.0, 1.0, 0.0};
    QQuaternion eye_rot = QQuaternion::fromAxisAndAngle(axis_y, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE); // creates a soft red image when background is white

    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    QQuaternion my_rot = rot2 * rot1;

    QMatrix4x4 matrix;
    matrix.translate(0.0, -0.25, -6.0);
    matrix.rotate(my_rot);
    // Set modelview-projection matrix
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);
    m_program.setUniformValue("rot_matrix", matrix);

    // Draw cube geometry
    m_thingy->drawCubeGeometry(&m_program);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);


    glClear(GL_DEPTH_BUFFER_BIT);
    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE); // creates a cyan image when background is white


    // Set modelview-projection matrix
    my_rot = eye_rot * rot2 * rot1;
    QMatrix4x4 matrix2;
    matrix2.translate(0.0, -0.25, -6.0);
    matrix2.rotate(my_rot);

    m_mvp_matrix = m_projection * matrix2;
    m_rot_matrix = matrix2;

    m_program.setUniformValue("mvp_matrix", m_projection * matrix2);
    m_program.setUniformValue("rot_matrix", matrix2);

    // Draw cube geometry
    m_thingy->drawCubeGeometry(&m_program);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glFlush();
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

void Table::keyPressEvent(QKeyEvent* e)
{
    unsigned int a = e->key();
    if (a == Qt::Key_Up) { // up
        m_xrot -= 10.0;
        my_update();
    } else if (a == Qt::Key_Down) { // down
        m_xrot += 10.0;
        my_update();
    } else if (a == Qt::Key_Left) { // left
        m_yrot -= 10.0;
        my_update();
    } else if (a ==Qt::Key_Right) { // right
        m_yrot += 10.0;
        my_update();
    }
    QWidget::keyPressEvent(e);
}

void Table::keyReleaseEvent(QKeyEvent* e)
{
    QWidget::keyReleaseEvent(e);
}

void Table::my_update()
{
//    update();
}



