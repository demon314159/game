//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

AltTable::AltTable(const QMatrix4x4& mvp_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent)
    : QWidget(parent)
    , m_ball(-BACK_WIDTH / 2.0 - BALL_RADIUS, FRONT_POS + BALL_RADIUS, BACK_WIDTH / 2.0 + BALL_RADIUS, BACK_POS - BALL_RADIUS)
    , m_bat_on(false)
    , m_pitch_on(false)
    , m_ball_set(QImage())
    , m_image_set(image_set)
    , m_stacked_widget(stacked_widget)
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_mvp_matrix(mvp_matrix)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(980);
    setMinimumWidth(580);
    m_ball_set.load(":/ball_set.png");
    timer.start(33, this);
}

void AltTable::draw_ani_image(QPainter &painter, const QRect& rect, const AnimatedImage& img, bool on_flag)
{
    if (rect.intersects(img.rect())) {
        if (on_flag) {
            painter.drawImage(img.m_x, img.m_y, img.m_image);
        }
    }
}

QRect AltTable::ball_rect() const
{
    QPoint bp = w2s(m_ball.position());
    return QRect(bp.x() - 33, bp.y() - 33, bp.x() + 33, bp.y() + 33);
}

QRect AltTable::ball_last_rect() const
{
    QPoint bp = w2s(m_ball.last_position());
    return QRect(bp.x() - 33, bp.y() - 33, bp.x() + 33, bp.y() + 33);
}


void AltTable::draw_ball(QPainter &painter, const QRect& rect, const QImage& the_ball)
{
    QPoint bp = w2s(m_ball.position());
    QRect br =  QRect(bp.x() - 33, bp.y() - 33, bp.x() + 33, bp.y() + 33);

    if (rect.intersects(br)) {
//        if (m_ball_in_play) {
            painter.drawImage(bp.x() - 32, bp.y() - 32, the_ball);
//        }
    }
}

void AltTable::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    // w2s() function depends on these
    m_width = painter.viewport().width();
    m_height = painter.viewport().height();

    QVector3D bpn = m_ball.position();
    QVector3D bpn_left = bpn + QVector3D(-BALL_RADIUS, 0.0, 0.0);
    QVector3D bpn_right = bpn + QVector3D(BALL_RADIUS, 0.0, 0.0);
    QPoint bl = w2s(bpn_left);
    QPoint br = w2s(bpn_right);

    int ball_radius = (br.x() - bl.x() + 1) / 2;

    QImage the_ball;
    if (ball_radius >= 1 && ball_radius <= 32) {
        int xp = (ball_radius & 7) * 64;
        int yp = ((ball_radius >> 3) & 7) * 64;
        the_ball = m_ball_set.copy(xp, yp, 64, 64);
    } else {
        printf("<<< ball radius our of range: %d pixels >>>\n", ball_radius);
    }

    QRect rect = event->rect();
//    printf("rect = (%d, %d) %d * %d\n", rect.x(), rect.y(), rect.width(), rect.height());

    if (rect == painter.viewport()) {
        painter.drawImage(0, 0, m_image_set.m_baseline);
    } else {
        QImage base_rect = m_image_set.m_baseline.copy(rect);
        painter.drawImage(rect.x(), rect.y(), base_rect);
    }
    draw_ani_image(painter, rect, m_image_set.m_pitch, m_pitch_on);
    draw_ball(painter, rect, the_ball);
    draw_ani_image(painter, rect, m_image_set.m_bat, m_bat_on);
#ifdef NEVERMORE
        draw_ani_image(painter, m_image_set.m_target1);
        draw_ani_image(painter, m_image_set.m_target2);
        draw_ani_image(painter, m_image_set.m_target3);
        draw_ani_image(painter, m_image_set.m_target4);
        draw_ani_image(painter, m_image_set.m_target5);
        draw_ani_image(painter, m_image_set.m_target6);
        draw_ani_image(painter, m_image_set.m_target7);
#endif
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
        m_ball.hit(QVector3D(BAT_PIVOT_X, 0.0, BAT_PIVOT_Z));
    } else if (e->button() == Qt::RightButton) {
        if (!m_ball.in_play()) {
            m_ball.launch(QVector3D(0.0, BALL_RADIUS, -2.0));
            m_pitch_on = true;
            update(m_image_set.m_pitch.rect());
        }
    }
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
    QPoint res(m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}

void AltTable::timerEvent(QTimerEvent *)
{
    if (m_ball.in_play()) {
        m_ball.update();
        QRect br_before = ball_last_rect();
        QRect br_after = ball_rect();
        update(br_before.united(br_after));
    }
}
