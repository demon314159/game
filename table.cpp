//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>

#include <cmath>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_ani_angle1(0.0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_frame_count(0)
    , m_thingy(0)
    , m_texture(0)
{
    setMinimumHeight(512);
    setMinimumWidth((512 * 1920) / 1080);
}

Table::~Table()
{
    makeCurrent();
    delete m_thingy;
    delete m_texture;
    doneCurrent();
}

void Table::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initShaders();
    initTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus;
    timer.start(12, this);
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
    ++m_frame_count;
//    printf("frame count = %d\n", m_frame_count);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_texture->bind();

    bool regular = true;
    if (regular) {
      QVector3D my_axis = {1.0, 0.0, 0.0};
      QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, 30.0);
      QMatrix4x4 matrix;
      matrix.translate(0.0, -0.25, -5.5);
      matrix.rotate(my_rot);
      // Set modelview-projection matrix
      m_program.setUniformValue("mvp_matrix", m_projection * matrix);
      m_program.setUniformValue("rot_matrix", matrix);
    } else {
      QVector3D my_axis = {1.0, 0.0, 0.0};
      QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, 80);
      QMatrix4x4 matrix;
      matrix.translate(0.0, -3.00, -13.0);
      matrix.rotate(my_rot);
      // Set modelview-projection matrix
      m_program.setUniformValue("mvp_matrix", m_projection * matrix);
      m_program.setUniformValue("rot_matrix", matrix);
    }
    QVector3D ani_axis1 = {0.0, 1.0, 0.0};
    QQuaternion ani_rot1 = QQuaternion::fromAxisAndAngle(ani_axis1, m_ani_angle1);
    float ani_sel1 = 8.0;
    QMatrix4x4 ani_matrix1;
    ani_matrix1.translate(BAT_PIVOT_X, 0.0, BAT_PIVOT_Z);
    ani_matrix1.rotate(ani_rot1);
    ani_matrix1.translate(-BAT_PIVOT_X, 0.0, -BAT_PIVOT_Z);

    m_program.setUniformValue("ani_sel1", ani_sel1);
    m_program.setUniformValue("ani_matrix1", ani_matrix1);


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

void Table::initTextures()
{
    m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Table::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
//    mousePressPosition = QVector2D(e->localPos());
    m_ani_angle1 = 45.0;
    update();
}

void Table::mouseReleaseEvent(QMouseEvent *e)
{
    m_ani_angle1 = 0.0;
    update();
    // Mouse release position - mouse press position
//    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
//    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
//    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
//    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
//    angularSpeed += acc;
}

void Table::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
//    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
//    if (angularSpeed < 0.01) {
//        angularSpeed = 0.0;
//    } else {
        // Update rotation
//        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
//        update();
//    }
}

