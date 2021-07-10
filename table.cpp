//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>
#include <QPainter>


#include <cmath>

Table::Table(QMatrix4x4& mvp_matrix, QImage& image, QStackedWidget* stacked_widget, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_stacked_widget(stacked_widget)
    , m_timer_ready(false)
    , m_timer_step(0)
    , m_image(image)
    , m_calibration_radius(1)
    , m_ani_sel1(1.0)
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
    , m_thingy(0)
    , m_mvp_matrix(mvp_matrix)
{
    setMinimumHeight(980);
    setMinimumWidth(580);
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
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus;
//    timer.start(16, this);
//    timer.start(30, this);
//    timer.start(100, this);
    timer.start(50, this);
}

void Table::resizeGL(int w, int h)
{
    m_width = w;
    m_height = h;

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    printf("in resizeGL %d x %d aspect ratio = %7.3lf\n", w, h, aspect);
    const qreal zNear = 2.5, zFar = 15.0, fov = 45.0;
    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
    m_timer_step = 0;
}

void Table::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool regular = false;
    if (regular) {
      QVector3D my_axis = {1.0, 0.0, 0.0};
      QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, 30.0);
      QMatrix4x4 matrix;
      matrix.translate(0.0, -0.25, -5.5);
      matrix.rotate(my_rot);
      // Set modelview-projection matrix
      m_mvp_matrix = m_projection * matrix;
      m_program.setUniformValue("mvp_matrix", m_projection * matrix);
      m_program.setUniformValue("rot_matrix", matrix);
    } else {
      QVector3D my_axis = {1.0, 0.0, 0.0};
      QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, 90);
      QMatrix4x4 matrix;
      matrix.translate(0.0, 0.0, -13.0);
      matrix.rotate(my_rot);
      // Set modelview-projection matrix
      m_mvp_matrix = m_projection * matrix;
      m_program.setUniformValue("mvp_matrix", m_projection * matrix);
      m_program.setUniformValue("rot_matrix", matrix);
    }

//    m_ani_sel1 = 35.0;
    QMatrix4x4 ani_matrix1;
    QMatrix4x4 ani_matrix2;
    ani_matrix2.translate(-2.0, 0.0, 0.0);
    m_program.setUniformValue("ani_sel1", m_ani_sel1);
    m_program.setUniformValue("ani_matrix1", ani_matrix1);
    m_program.setUniformValue("ani_matrix2", ani_matrix2);

    // Draw cube geometry
    m_thingy->drawCubeGeometry(&m_program);
//    for (int i = 1; i < 70; i++) {
//        float r = 0.005 * (float) i;

//        QVector3D a(0.0, 0.0, 0.0);
//        QVector3D b(r, 0.0, 0.0);
//        QPoint sa = w2s(a);
//        QPoint sb = w2s(b);
//        printf("r = %7.3f, radius = %d pixels\n", r, sb.x() - sa.x() + 1);
//    }
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

#ifdef NEVERMORE
void Table::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
//    mousePressPosition = QVector2D(e->localPos());
//

    if (e->button() == Qt::LeftButton) {
        m_ani_angle1 = 45.0 + 30.0;
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
#endif

float3 Table::ball_position_now()
{
    float3 res;

    if (m_ball_in_play) {
        if (m_ball_hit) {
                int tdiff = m_th - m_t0;
                m_hit_pos = {0.0, 0.25, -2.0f + 6.0f * ((float) tdiff) / 1000.0f};
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
#ifdef NEVERMORE
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
#endif

QPoint Table::w2s(const QVector3D point) const
{

    QVector4D sp = m_mvp_matrix * QVector4D(point, 1.0);
    QPoint res(m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}

bool Table::grab_image(int slot, QImage& image)
{
    if (m_timer_step == slot) {
        printf("grabbing slot %d\n", slot);
        update();
        ++m_timer_step;
        return true;
    } else if (m_timer_step == (slot + 1)) {
        image = grabFramebuffer();
        printf("has alpha channel: %s\n", image.hasAlphaChannel()?"yes":"no");
        ++m_timer_step;
        return true;
    }
    return false;
}

bool Table::grab_ani_image(int slot, AnimatedImage& ai)
{
    if (m_timer_step == slot) {
        printf("grabbing slot %d\n", slot);
        update();
        ++m_timer_step;
        return true;
    } else if (m_timer_step == (slot + 1)) {
        ai.m_image = grabFramebuffer();
        ai.m_x = 0;
        ai.m_y = 0;
        ++m_timer_step;
        return true;
    }
    return false;
}

int Table::image_radius()
{
    const int box_w = 200;

    QImage fb = grabFramebuffer();
    QImage box = fb.copy((fb.width() - box_w) / 2, (fb.height() - box_w) / 2, box_w, box_w);
    int nx = box.width();
    int ny = box.height();
    int x1 = 0;
    int x2 = box.width() - 1;
    int y1 = 0;
    int y2 = box.height() - 1;
    int minx = x2;
    int maxx = x1;
    int miny = y2;
    int maxy = y1;
    for (int j = 0; j < ny; j++) {
        uchar* box_line = box.scanLine(j);
        for (int i = 0; i < nx; i++) {
            if ( box_line[4 * i]     != 0
              || box_line[4 * i + 1] != 255
              || box_line[4 * i + 2] != 255) {
                maxx = std::max(maxx, i);
                minx = std::min(minx, i);
                maxy = std::max(maxy, j);
                miny = std::min(miny, j);
            } else {
                box_line[4 * i] = 0;
                box_line[4 * i + 1] = 0;
                box_line[4 * i + 2] = 0;
                box_line[4 * i + 3] = 0;
            }
        }
    }
    if (maxx != x1 || minx != x2) {
        x1 = minx;
        x2 = maxx;
    }
    if (maxy != y1 || miny != y2) {
        y1 = miny;
        y2 = maxy;
    }
    printf("    x1 = %d, x2 = %d, y1 = %d, y2 = %d, center = (%d, %d)\n", x1, x2, y1, y2, (x1 + x2) / 2, (y1 + y2) / 2);
    int radius1 = (x2 - x1 + 1) / 2;
    int radius2 = (y2 - y1 + 1) / 2;
    int radius = std::max(radius1, radius2);
    QImage img = box.copy(36, 36, 128, 128);
    if (radius >= 1 && radius <= 64) {
        int x = ((radius-1) & 7) * 128;
        int y = (((radius-1) >> 3) & 7) * 128;
        QPainter painter;
        painter.begin(&m_image);
        painter.drawImage(x, y, img);
        painter.end();
    }
    return radius;
}

void Table::timerEvent(QTimerEvent *)
{
    if (isVisible()) {
//        printf("timer step %d\n", m_timer_step);
        int base = 10;
        if (m_timer_step >= base) {
            if (m_timer_ready) {
                if (m_timer_step == base) {
                    m_calibration_radius = image_radius();
                    printf("step 1b: resulting radius = %d pixels\n", m_calibration_radius);
                } else {
                    int radius = image_radius();
                    printf("step %db: resulting radius = %d pixels\n", m_timer_step - base + 1, radius);
                }
                ++m_timer_step;
                m_timer_ready = false;
            } else {
//                m_ani_sel1 = (float) (m_timer_step - base);
                if (m_timer_step == base) {
                    printf("step 1a: setting up calibration image size 1.0\n");
                    m_ani_sel1 = 1.0;
                    update();
                } else {
                    m_ani_sel1 = (float) (m_timer_step - base) / (float) m_calibration_radius;
                    printf("step %da: setting up calibration image size %7.3f\n", m_timer_step - base + 1, m_ani_sel1);
                    update();
                }
                m_timer_ready = true;
            }
        } else {
            ++m_timer_step;
        }

        if (m_timer_step == (base + 65)) {
            printf("Handover\n");
#ifdef GUY_SET
            m_image.save("new_guy_set.png");
#else
            m_image.save("new_ball_set.png");
#endif
            m_stacked_widget->setCurrentIndex(1);
            ++m_timer_step;
            return;
        }
    }
}


