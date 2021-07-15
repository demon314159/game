//
// table.cpp
//
#include "table.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(int& view_ix, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_timer_step(0)
    , m_tilt(0.0)
    , m_target_ani_id(0.0)
    , m_bat_angle(0.0)
    , m_ani_angle2(0.0)
    , m_ani_angle3(0.0)
    , m_ball_in_play(false)
    , m_ball_hit(false)
    , m_outs(0)
    , m_left_digit(-1)
    , m_middle_digit(-1)
    , m_right_digit(-1)
    , m_t0(0)
    , m_th(0)
    , m_ball_pos0({0.0, -0.25, 0.0})
    , m_hit_pos({0.0, 0.0, 0.0})


    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_thingy(NULL)
    , m_view_ix(view_ix)
    , m_mvp_matrix(mvp_matrix)
    , m_rot_matrix(rot_matrix)
{
    if (m_view_ix == 2) {
        m_tilt = 90.0;
        setMinimumHeight(1834);
        setMinimumWidth(1062);
    } else if (m_view_ix == 1) {
        m_tilt = 35.0;
        setMinimumHeight(994);
        setMinimumWidth(1902);
    } else {
        m_tilt = 90.0;
        setMinimumHeight(994);
        setMinimumWidth(580);
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus(m_tilt);
//    timer.start(16, this);
    timer.start(15, this);
//    timer.start(100, this);
}

void Table::resizeGL(int w, int h)
{
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

    if (m_view_ix == 1) {
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
    } else { // m_viewIx == 0 or m_view_ix == 2
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

    QVector3D ani_axis1 = {0.0, 1.0, 0.0};
    QQuaternion ani_rot1 = QQuaternion::fromAxisAndAngle(ani_axis1, m_bat_angle);
    float bat_ani_id = ANI_ID_BAT;
    QMatrix4x4 bat_matrix;
    bat_matrix.translate(BAT_PIVOT_X, 0.0, BAT_PIVOT_Z);
    bat_matrix.rotate(ani_rot1);
    bat_matrix.translate(-BAT_PIVOT_X, 0.0, -BAT_PIVOT_Z);
    m_program.setUniformValue("bat_ani_id", bat_ani_id);
    m_program.setUniformValue("bat_matrix", bat_matrix);

    QVector3D ani_axis2 = {1.0, 0.0, 0.0};
    QQuaternion ani_rot2 = QQuaternion::fromAxisAndAngle(ani_axis2, m_ani_angle2);
    QMatrix4x4 ani_matrix2;
    ani_matrix2.translate(0.0, TARGET_PIVOT_Y, TARGET_PIVOT_Z);
    ani_matrix2.rotate(ani_rot2);
    ani_matrix2.translate(0.0, -TARGET_PIVOT_Y, -TARGET_PIVOT_Z);
    m_program.setUniformValue("target_ani_id", m_target_ani_id);
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


    float left_digit = m_left_digit == -1 ? 0.0 : 30.0 + (float) m_left_digit;
    float middle_digit = m_middle_digit == -1 ? 0.0 : 20.0 + (float) m_middle_digit;
    float right_digit = m_right_digit == -1 ? 0.0 : 10.0 + (float) m_right_digit;
    float left_out = 0.0;   // 40.0
    float middle_out = 0.0; // 41.0
    float right_out = 0.0;  // 42.0
    float light_sel = 52.0;
    if (m_outs == 1) {
        left_out = 40.0;
    } else if (m_outs == 2) {
        left_out = 40.0;
        middle_out = 41.0;
    } else if (m_outs == 3) {
        left_out = 40.0;
        middle_out = 41.0;
        right_out = 42.0;
    }
    QMatrix4x4 digit_matrix;
    digit_matrix.translate(0.0, 0.1, 0.0);
    m_program.setUniformValue("left_digit", left_digit);
    m_program.setUniformValue("middle_digit", middle_digit);
    m_program.setUniformValue("right_digit", right_digit);
    m_program.setUniformValue("left_out", left_out);
    m_program.setUniformValue("middle_out", middle_out);
    m_program.setUniformValue("right_out", right_out);
    m_program.setUniformValue("digit_matrix", digit_matrix);
    m_program.setUniformValue("light_sel", light_sel);

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

bool Table::grab_image(int slot, QImage& image)
{
    if (m_timer_step == slot) {
//        printf("grabbing slot %d\n", slot);
        update();
        ++m_timer_step;
        return true;
    } else if (m_timer_step == (slot + 1)) {
        image = grabFramebuffer();
        ++m_timer_step;
        return true;
    }
    return false;
}

bool Table::grab_ani_image(int slot, AnimatedImage& ai)
{
    if (m_timer_step == slot) {
//        printf("grabbing slot %d\n", slot);
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
void Table::timerEvent(QTimerEvent *)
{
    if (isVisible()) {

//        printf("timer step %d\n", m_timer_step);
        int base = 10;
        if (grab_image(base, m_image_set.m_baseline))
            return;
        m_bat_angle = 45.0 + 30.0;
        if (grab_ani_image(base + 2, m_image_set.m_bat))
            return;
        m_bat_angle = 0.0;
        m_ani_angle3 = -15.0;
        if (grab_ani_image(base + 4, m_image_set.m_pitch))
            return;
        m_ani_angle3 = 0.0;
        m_ani_angle2 = -60.0;
        m_target_ani_id = ANI_ID_TARGET1;
        if (grab_ani_image(base + 6, m_image_set.m_target[0]))
            return;
        m_target_ani_id = ANI_ID_TARGET2;
        if (grab_ani_image(base + 8, m_image_set.m_target[1]))
            return;
        m_target_ani_id = ANI_ID_TARGET3;
        if (grab_ani_image(base + 10, m_image_set.m_target[2]))
            return;
        m_target_ani_id = ANI_ID_TARGET4;
        if (grab_ani_image(base + 12, m_image_set.m_target[3]))
            return;
        m_target_ani_id = ANI_ID_TARGET5;
        if (grab_ani_image(base + 14, m_image_set.m_target[4]))
            return;
        m_target_ani_id = ANI_ID_TARGET6;
        if (grab_ani_image(base + 16, m_image_set.m_target[5]))
            return;
        m_target_ani_id = ANI_ID_TARGET7;
        if (grab_ani_image(base + 18, m_image_set.m_target[6]))
            return;
        m_bat_angle = 0.0;
        m_ani_angle2 = 0.0;
        m_ani_angle3 = 0.0;
        m_target_ani_id = 0.0;
        m_outs = 1;
        if (grab_ani_image(base + 20, m_image_set.m_outs[0]))
            return;
        m_outs = 2;
        if (grab_ani_image(base + 22, m_image_set.m_outs[1]))
            return;
        m_outs = 3;
        if (grab_ani_image(base + 24, m_image_set.m_outs[2]))
            return;
        m_outs = 0;

        if (grab_digit_set(base + 26, m_right_digit, m_image_set.m_right_digit))
            return;
        if (grab_digit_set(base + 46, m_middle_digit, m_image_set.m_middle_digit))
            return;
        if (grab_digit_set(base + 66, m_left_digit, m_image_set.m_left_digit))
            return;

        if (m_timer_step == (base + 86)) {
            update();
            ++m_timer_step;
            m_image_set.difference(m_image_set.m_bat);
            m_image_set.difference(m_image_set.m_pitch);
            m_image_set.difference(m_image_set.m_target[0]);
            m_image_set.difference(m_image_set.m_target[1]);
            m_image_set.difference(m_image_set.m_target[2]);
            m_image_set.difference(m_image_set.m_target[3]);
            m_image_set.difference(m_image_set.m_target[4]);
            m_image_set.difference(m_image_set.m_target[5]);
            m_image_set.difference(m_image_set.m_target[6]);
            m_image_set.difference(m_image_set.m_outs[0]);
            m_image_set.difference(m_image_set.m_outs[1]);
            m_image_set.difference(m_image_set.m_outs[2]);
            digit_difference(m_image_set.m_right_digit);
            digit_difference(m_image_set.m_middle_digit);
            digit_difference(m_image_set.m_left_digit);
            return;
        }
        if (m_timer_step == (base + 87)) {
            printf("Handover\n");
            m_stacked_widget->setCurrentIndex(1);
            ++m_timer_step;
            return;
        }
        ++m_timer_step;
    }
}

bool Table::grab_digit_set(int index, int& adigit, AnimatedImage (&digit)[ImageSet::DIGITS])
{
    adigit = 0;
    if (grab_ani_image(index, digit[0]))
        return true;
    adigit = 1;
    if (grab_ani_image(index + 2, digit[1]))
        return true;
    adigit = 2;
    if (grab_ani_image(index + 4, digit[2]))
        return true;
    adigit = 3;
    if (grab_ani_image(index + 6, digit[3]))
        return true;
    adigit = 4;
    if (grab_ani_image(index + 8, digit[4]))
        return true;
    adigit = 5;
    if (grab_ani_image(index + 10, digit[5]))
        return true;
    adigit = 6;
    if (grab_ani_image(index + 12, digit[6]))
        return true;
    adigit = 7;
    if (grab_ani_image(index + 14, digit[7]))
        return true;
    adigit = 8;
    if (grab_ani_image(index + 16, digit[8]))
        return true;
    adigit = 9;
    if (grab_ani_image(index + 18, digit[9]))
        return true;
    adigit = -1;
    return false;
}

void Table::digit_difference(AnimatedImage (&digit)[ImageSet::DIGITS])
{
    m_image_set.difference(digit[0]);
    m_image_set.difference(digit[1]);
    m_image_set.difference(digit[2]);
    m_image_set.difference(digit[3]);
    m_image_set.difference(digit[4]);
    m_image_set.difference(digit[5]);
    m_image_set.difference(digit[6]);
    m_image_set.difference(digit[7]);
    m_image_set.difference(digit[8]);
    m_image_set.difference(digit[9]);
}

QImage Table::the_image()
{
    return m_image;
}
