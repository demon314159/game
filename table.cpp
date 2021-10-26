//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(int& view_ix, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_ms_at_start(QTime::currentTime().msecsSinceStartOfDay())
    , m_xrot(0.0)
    , m_yrot(0.0)
    , m_aspect(1.0)
    , m_camz(8.0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
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
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//
//
//    glClearColor(0.7f, 0.7f, 0.3f, 1.0f);



//    glClearColor(1.0f, 0.8f, 0.8f, 1.0f); // pink


//    glClearColor(1.0f, 1.0f, 0.4f, 1.0f); // yellow
    glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange




//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus();
    resize_calc();
    timer.start(33, this);
}

void Table::resize_calc()
{
    float znear = m_camz;
    float zfar = (m_thingy == NULL) ? m_camz * 4.0 : m_camz + 2.0 * m_thingy->rad_xz();
    float fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, m_aspect, znear, zfar);
}


void Table::resizeGL(int w, int h)
{
    m_aspect = qreal(w) / qreal(h ? h : 1);
    resize_calc();
}

void Table::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    QQuaternion my_rot = rot1 * rot2;

    QMatrix4x4 matrix;
    float rad_xz = (m_thingy == NULL) ? 2.0 : m_thingy->rad_xz();
    float3 center = (m_thingy == NULL) ? float3{0.0, 0.0, 0.0} : m_thingy->center();
    matrix.translate(0.0, 0.0, -m_camz - rad_xz);
    matrix.rotate(my_rot);
    matrix.translate(-center.v1, -center.v2, -center.v3);
    // Set modelview-projection matrix
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);
    m_program.setUniformValue("rot_matrix", matrix);

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
//        update();
    }
}

void Table::keyPressEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    if (a == 0x6f) { // up
        if (e->modifiers() & Qt::ShiftModifier)
            m_xrot -= 1.0;
        else
            m_xrot -= 10.0;
        update();
    } else if (a == 0x74) { // down
        if (e->modifiers() & Qt::ShiftModifier)
            m_xrot += 1.0;
        else
            m_xrot += 10.0;
        update();
    } else if (a == 0x71) { // left
        if (e->modifiers() & Qt::ShiftModifier)
            m_yrot -= 1.0;
        else
            m_yrot -= 10.0;
        update();
    } else if (a == 0x72) { // right
        if (e->modifiers() & Qt::ShiftModifier)
            m_yrot += 1.0;
        else
            m_yrot += 10.0;
        update();
    } else if (a == 0x1f) { // i or I
        if (e->modifiers() & Qt::ShiftModifier)
            m_camz *= (29.0 / 30.0);
        else
            m_camz *= (2.0 / 3.0);
        resize_calc();
        update();
    } else if (a == 0x20) { // o or O
        if (e->modifiers() & Qt::ShiftModifier)
            m_camz *= (30.0 / 29.0);
        else
           m_camz *= (3.0 / 2.0);
        resize_calc();
        update();
    } else if (a == 0x2b) { // h or H
        m_camz = 8.0;
        m_xrot = 0.0;
        m_yrot = 0.0;
        resize_calc();
        update();
    }
    QWidget::keyPressEvent(e);
}

void Table::keyReleaseEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    if (a == 0x32) {
    } else if (a == 0x3e) {
    }
    QWidget::keyReleaseEvent(e);
}





