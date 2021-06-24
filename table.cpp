//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_ani_angle1(0.0)
    , m_ani_angle2(0.0)
    , m_ani_angle3(0.0)
    , m_ball_in_play(false)
    , m_ball_hit(false)
    , m_blocker(false)
    , m_t0(0)
    , m_th(0)
    , m_ball_pos0({0.0, -0.25, 0.0})
    , m_hit_pos({0.0, 0.0, 0.0})


    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_frame_count(0)
    , m_thingy(0)
    , m_texture(0)
{
    setMinimumHeight(980);
    setMinimumWidth(580);
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
    timer.start(30, this);
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

    bool regular = false;
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
      QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, 90);
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

    QVector3D ani_axis2 = {1.0, 0.0, 0.0};
    QQuaternion ani_rot2 = QQuaternion::fromAxisAndAngle(ani_axis2, m_ani_angle2);
    float ani_sel2 = 5.0;
    QMatrix4x4 ani_matrix2;
    ani_matrix2.translate(0.0, TARGET_PIVOT_Y, TARGET_PIVOT_Z);
    ani_matrix2.rotate(ani_rot2);
    ani_matrix2.translate(0.0, -TARGET_PIVOT_Y, -TARGET_PIVOT_Z);
    m_program.setUniformValue("ani_sel2", ani_sel2);
    m_program.setUniformValue("ani_matrix2", ani_matrix2);

    QVector3D ani_axis3 = {1.0, 0.0, 0.0};
    QQuaternion ani_rot3 = QQuaternion::fromAxisAndAngle(ani_axis3, m_ani_angle3);
    float ani_sel3 = 9.0;
    QMatrix4x4 ani_matrix3;
    ani_matrix3.translate(0.0, 0.0, PITCH_PIVOT_Z);
    ani_matrix3.rotate(ani_rot3);
    ani_matrix3.translate(0.0, 0.0, -PITCH_PIVOT_Z);
    m_program.setUniformValue("ani_sel3", ani_sel3);
    m_program.setUniformValue("ani_matrix3", ani_matrix3);

    float3 bpn = ball_position_now();
    float ani_sel4 = 10.0;
    QMatrix4x4 ani_matrix4;
    ani_matrix4.translate(bpn.v1, bpn.v2, bpn.v3);
    m_program.setUniformValue("ani_sel4", ani_sel4);
    m_program.setUniformValue("ani_matrix4", ani_matrix4);

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
//

    if (e->button() == Qt::LeftButton) {
        m_ani_angle1 = 45.0 + 30.0;
        QImage fb = grabFramebuffer();
        printf("grabbed image %d * %d\n", fb.width(), fb.height());
        if (m_ball_in_play && !m_ball_hit) {
            m_th = QTime::currentTime().msecsSinceStartOfDay();
            m_ball_hit = true;
        }
        update();
    } else if (e->button() == Qt::RightButton) {
//        if (!m_ball_in_play) {
            m_t0 = QTime::currentTime().msecsSinceStartOfDay();
            m_ball_pos0 = {0.0, 0.25, -2.0};
            m_ball_hit = false;
            m_blocker = false;
            m_ball_in_play = true;
            m_ani_angle3 = -15.0;
            update();
//        }
    }
}

float3 Table::ball_position_now()
{
    float3 res;

    if (m_ball_in_play) {
        if (m_ball_hit) {
                int tdiff = m_th - m_t0;
                m_hit_pos = {0.0, 0.25, -2.0 + 6.0 * (float) tdiff / 1000.0};
                float dx = BAT_PIVOT_X;
                float dz = BAT_PIVOT_Z - m_hit_pos.v3;
                float theta = atanf(dz / dx);
                float vx = 2.0 * 6.0 * sin(theta);
                float vz = 2.0 * 6.0 * cos(theta);
//                printf("hit_pos = %7.3lf, %7.3lf\n", m_hit_pos.v1, m_hit_pos.v3);
//                printf("bat_pos = %7.3lf, %7.3lf\n", BAT_PIVOT_X, BAT_PIVOT_Z);
//                printf("dx = %7.3lf, dz = %7.3lf\n", BAT_PIVOT_X - m_hit_pos.v1, BAT_PIVOT_Z - m_hit_pos.v3);

//                printf("theta = %7.3f, vx = %7.3f, vz = %7.3f\n", theta * 180.0 / 3.14159, vx, vz);
            int tnow = QTime::currentTime().msecsSinceStartOfDay();
            tdiff = tnow - m_th;
            res.v1 = vx * (float) tdiff / 1000.0;
            res.v2 = 0.0;
            res.v3 = m_hit_pos.v3 - vz * (float) tdiff / 1000.0;
        } else {
            int tnow = QTime::currentTime().msecsSinceStartOfDay();
            int tdiff = tnow - m_t0;
            res.v1 = 0.0;
            res.v2 = 0.25;
            res.v3 = -2.0 + 6.0 * (float) tdiff / 1000.0;
        }
    } else {
        res = {0.0, -1.00, 0.0};
    }
    return res;
}

void Table::mouseReleaseEvent(QMouseEvent *e)
{
    m_ani_angle1 = 0.0;
    m_ani_angle2 = 0.0;
    m_ani_angle3 = 0.0;
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
    if (m_ball_in_play) {
        float3 bpn = ball_position_now();
        if (bpn.v3 < -8 || bpn.v3 > 2) {
            m_ball_in_play = false;
        }
        update();
    }
}

