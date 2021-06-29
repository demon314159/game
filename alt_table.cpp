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
    timer.start(30, this);
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
            printf("drawing little picture on\n");
        }
    }
}

void AltTable::paintEvent(QPaintEvent* event)
{




    QPainter painter(this);
    // w2s() function depends on these
    m_width = painter.viewport().width();
    m_height = painter.viewport().height();
    m_x_base = painter.viewport().left();
    m_y_base = painter.viewport().top();


    QVector3D ball_center(0.0, 0.125, 0.0);
    QVector3D ball_right(0.125, 0.125, 0.0);
    QPoint bc = w2s(ball_center);
    QPoint br = w2s(ball_right);

    printf("bc(x,y) = %d %d\n", bc.x(), bc.y());
    printf("br(x,y) = %d %d\n", br.x(), br.y());
    int ball_radius = br.x() - bc.x();
    printf("ball radius = %d\n", ball_radius);



//    int th = text_height(painter, QString("0"));

//    painter.setPen(Qt::black);
   QRect rect = event->rect();
   printf("rect = (%d, %d) %d * %d\n", rect.x(), rect.y(), rect.width(), rect.height());


    if (rect == painter.viewport()) {
        painter.drawImage(0, 0, m_image_set.m_baseline);
        printf("drawing big picture\n");
    } else {
        QImage base_rect = m_image_set.m_baseline.copy(rect);
        painter.drawImage(rect.x(), rect.y(), base_rect);
    }
    draw_ani_image(painter, rect, m_image_set.m_bat, m_bat_on);
    draw_ani_image(painter, rect, m_image_set.m_pitch, m_pitch_on);
    painter.setPen(Qt::red);
    painter.drawEllipse(bc.x() - ball_radius, bc.y() - ball_radius, ball_radius*2, ball_radius*2);
#ifdef NEVERMORE

        draw_ani_image(painter, m_image_set.m_target1);
    else if (m_image_sel == 4)
        draw_ani_image(painter, m_image_set.m_target2);
    else if (m_image_sel == 5)
        draw_ani_image(painter, m_image_set.m_target3);
    else if (m_image_sel == 6)
        draw_ani_image(painter, m_image_set.m_target4);
    else if (m_image_sel == 7)
        draw_ani_image(painter, m_image_set.m_target5);
    else if (m_image_sel == 8)
        draw_ani_image(painter, m_image_set.m_target6);
    else if (m_image_sel == 9)
        draw_ani_image(painter, m_image_set.m_target7);
#endif


    painter.setPen(Qt::black);


    QVector3D tp1(-front_width / 2.0, 0.0, front_pos);
    QVector3D tp2(front_width / 2.0, 0.0, front_pos);
    QVector3D tp3(back_width / 2.0, 0.0, back_pos);
    QVector3D tp4(-back_width / 2.0, 0.0, back_pos);
    QVector3D tp0(0.0, 0.125, 0.0);

    QPoint sp1 = w2s(tp1);
    QPoint sp2 = w2s(tp2);
    QPoint sp3 = w2s(tp3);
    QPoint sp4 = w2s(tp4);
    QPoint sp0 = w2s(tp0);

    int x1 = sp1.x();
    int y1 = sp1.y();

    int x2 = sp2.x();
    int y2 = sp2.y();

    int x3 = sp3.x();
    int y3 = sp3.y();

    int x4 = sp4.x();
    int y4 = sp4.y();

    int x0 = sp0.x();
    int y0 = sp0.y();


    printf("x0,y0 = %d, %d\n", x0, y0);
    printf("x1,y1 = %d, %d\n", x1, y1);
    printf("x2,y2 = %d, %d\n", x2, y2);
    printf("x3,y3 = %d, %d\n", x3, y3);
    printf("x4,y4 = %d, %d\n", x4, y4);

    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x2, y2, x3, y3);
    painter.drawLine(x3, y3, x4, y4);
    painter.drawLine(x4, y4, x1, y1);
    painter.drawLine(x1, y1, x0, y0);
    painter.drawLine(x2, y2, x0, y0);
    painter.drawLine(x3, y3, x0, y0);
    painter.drawLine(x4, y4, x0, y0);



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
//        if (m_ball_in_play && !m_ball_hit) {
//            m_th = QTime::currentTime().msecsSinceStartOfDay();
//            m_ball_hit = true;

// missing ball update


//        }
    } else if (e->button() == Qt::RightButton) {
        if (!m_ball_in_play) {
            m_pitch_on = true;
            update(m_image_set.m_pitch.rect());
//            m_t0 = QTime::currentTime().msecsSinceStartOfDay();
//            m_ball_pos0 = {0.0, 0.25, -2.0};
//            m_ball_hit = false;
//            m_blocker = false;
//            m_ball_in_play = true;

// missing ball update



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
            float vx = 2.0 * 6.0 * sin(theta);
            float vz = 2.0 * 6.0 * cos(theta);
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
#ifdef NEVERMORE
    if (m_ball_in_play) {
        QVector3D bpn = ball_position_now();
        if (bpn.x() < (-back_width / 2.0)
         || bpn.x() > (back_width / 2.0)
         || bpn.z() < (back_pos - 1.0)
         || bpn.z() > (front_pos + 1.0)) {
            m_ball_in_play = false;
        }


// missing update for ball animation

        update(); // do whole screen for now


    }
#endif


}
