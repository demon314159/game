//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>
#include <QTime>

AltTable::AltTable(const QMatrix4x4& mvp_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QWidget(parent)
    , m_bat_on(false)
    , m_pitch_on(false)
    , m_ball_in_play(false)
    , m_ball_hit(false)
    , m_blocker(false)
    , m_t0(0)
    , m_th(0)
    , m_ball_radius(18)
    , m_new_ball_pos(QPoint(0,0))
    , m_old_ball_pos(QPoint(0,0))
    , m_ball_pos0(QVector3D(0.0, -0.25, 0.0))
    , m_hit_pos(QVector3D(0.0, 0.0, 0.0))
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_x_base(0)
    , m_y_base(0)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_mvp_matrix(mvp_matrix)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(980);
    setMinimumWidth(580);
    timer.start(15, this);
}

int AltTable::text_width(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.width();
}

int AltTable::text_height(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.height();
}


void AltTable::draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag)
{
    if (rect.intersects(img.rect())) {
        if (on_flag) {
            painter.drawImage(img.m_x, img.m_y, img.m_image);
        }
    }
}

QRect AltTable::ball_rect(const QPoint& center) const
{
    return QRect(center.x() - m_ball_radius - 1, center.y() - m_ball_radius - 1, center.x() + m_ball_radius + 1, center.y() + m_ball_radius + 1);
}

void AltTable::draw_ball(QPainter &painter, const QRect& rect)
{

    if (rect.intersects(ball_rect(m_new_ball_pos))) {
//        if (m_ball_in_play) {
            painter.drawEllipse(m_new_ball_pos.x() - m_ball_radius, m_new_ball_pos.y() - m_ball_radius, m_ball_radius * 2, m_ball_radius * 2);
        }
//    }
}

void AltTable::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // w2s() function depends on these
    m_width = painter.viewport().width();
    m_height = painter.viewport().height();
    m_x_base = painter.viewport().left();
    m_y_base = painter.viewport().top();

    QVector3D bpn_center = ball_position_now();
    QVector3D bpn_right = bpn_center + QVector3D(0.1, 0.0, 0.0);
    QPoint bc = w2s(bpn_center);
    QPoint br = w2s(bpn_right);

    m_ball_radius = br.x() - bc.x();

    QRect rect = event->rect();
//    printf("rect = (%d, %d) %d * %d\n", rect.x(), rect.y(), rect.width(), rect.height());

    if (rect == painter.viewport()) {
        painter.drawImage(0, 0, m_image_set.m_baseline);
    } else {
        QImage base_rect = m_image_set.m_baseline.copy(rect);
        painter.drawImage(rect.x(), rect.y(), base_rect);
    }
    draw_ani_image(painter, rect, m_image_set.m_bat, m_bat_on);
    draw_ani_image(painter, rect, m_image_set.m_pitch, m_pitch_on);
    painter.setPen(Qt::red);
    draw_ball(painter, rect);
#ifdef NEVERMORE
        draw_ani_image(painter, m_image_set.m_target1);
        draw_ani_image(painter, m_image_set.m_target2);
        draw_ani_image(painter, m_image_set.m_target3);
        draw_ani_image(painter, m_image_set.m_target4);
        draw_ani_image(painter, m_image_set.m_target5);
        draw_ani_image(painter, m_image_set.m_target6);
        draw_ani_image(painter, m_image_set.m_target7);
#endif

//    if (m_ball_in_play) {
//        QPoint spoint = w2s(ball_position_now());
//
//        painter.drawImage(spoint.x() -25, spoint.y() + 25, zimg);
//
//    }

}


void AltTable::resizeEvent(QResizeEvent*)
{
    if (isVisible()) {
        printf("resize handback\n");
        m_stacked_widget->setCurrentIndex(0);
    }
}

void AltTable::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_bat_on = true;
        update(m_image_set.m_bat.rect());
        if (m_ball_in_play && !m_ball_hit) {
            m_th = QTime::currentTime().msecsSinceStartOfDay();
            m_ball_hit = true;
        }
    } else if (e->button() == Qt::RightButton) {
        if (!m_ball_in_play) {
            m_pitch_on = true;
            update(m_image_set.m_pitch.rect());
            m_t0 = QTime::currentTime().msecsSinceStartOfDay();
            m_ball_pos0 = {0.0, 0.25, -2.0};
            m_ball_hit = false;
            m_blocker = false;
            m_ball_in_play = true;
        }
    }
}

QVector3D AltTable::ball_position_now()
{
    QVector3D res;

    if (m_ball_in_play) {
        if (m_ball_hit) {
            int tdiff = m_th - m_t0;
            m_hit_pos = QVector3D(0.0, 0.25, -2.0 + 6.0 * (float) tdiff / 1000.0);
            float dx = BAT_PIVOT_X;
            float dz = BAT_PIVOT_Z - m_hit_pos.z();
            float theta = atanf(dz / dx);
            float vx = 4.0 * 6.0 * sin(theta);
            float vz = 4.0 * 6.0 * cos(theta);
//                printf("hit_pos = %7.3lf, %7.3lf\n", m_hit_pos.v1, m_hit_pos.v3);
//                printf("bat_pos = %7.3lf, %7.3lf\n", BAT_PIVOT_X, BAT_PIVOT_Z);
//                printf("dx = %7.3lf, dz = %7.3lf\n", BAT_PIVOT_X - m_hit_pos.v1, BAT_PIVOT_Z - m_hit_pos.v3);

//                printf("theta = %7.3f, vx = %7.3f, vz = %7.3f\n", theta * 180.0 / 3.14159, vx, vz);
            int tnow = QTime::currentTime().msecsSinceStartOfDay();
            tdiff = tnow - m_th;
            res = QVector3D(vx * (float) tdiff / 1000.0, 0.0, m_hit_pos.z() - vz * (float) tdiff / 1000.0);
        } else {
            int tnow = QTime::currentTime().msecsSinceStartOfDay();
            int tdiff = tnow - m_t0;
            res = QVector3D(0.0, 0.25, -2.0 + 6.0 * (float) tdiff / 1000.0);
        }
    } else {
        res = QVector3D(0.0, 1.00, 0.0);
    }
    return res;
}

void AltTable::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_bat_on = false;
        update(m_image_set.m_bat.rect());
    } else if (e->button() == Qt::RightButton) {
        m_pitch_on = false;
        update(m_image_set.m_pitch.rect());
    }
}

QPoint AltTable::w2s(const QVector3D point) const
{

    QVector4D sp = m_mvp_matrix * QVector4D(point, 1.0);
    QPoint res(m_x_base + m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_y_base + m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}

void AltTable::timerEvent(QTimerEvent *)
{
    if (m_ball_in_play) {
        m_old_ball_pos = m_new_ball_pos;
        m_new_ball_pos = w2s(ball_position_now());
        update(ball_rect(m_new_ball_pos).united(ball_rect(m_old_ball_pos)));
        QVector3D bpn = ball_position_now();
        if (bpn.x() < (-back_width / 2.0)
         || bpn.x() > (back_width / 2.0)
         || bpn.z() < (back_pos)
         || bpn.z() > (front_pos)) {
            m_ball_in_play = false;
        }
    }
}
