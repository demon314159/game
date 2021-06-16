//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>

#include <cmath>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_width(512)
    , m_height(512)
    , m_frame_count(0)
    , m_thingy(0)
    , m_texture(0)
{
    setMinimumHeight(512);
    setMinimumWidth(512);
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
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void Table::paintGL()
{
    ++m_frame_count;
//    printf("frame count = %d\n", m_frame_count);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_texture->bind();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);

    // Use texture unit 0 which contains cube.png
    m_program.setUniformValue("texture", 0);

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
    mousePressPosition = QVector2D(e->localPos());
}

void Table::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void Table::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

