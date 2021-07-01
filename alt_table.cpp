//
// alt_table.cpp
//
#include "alt_table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>
#include <QTime>

AltTable::AltTable(const QMatrix4x4& mvp_matrix, QImage& image, QStackedWidget* stacked_widget, QWidget *parent)
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
    , m_image(image)
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


QRect AltTable::ball_rect(const QPoint& center) const
{
    return QRect(center.x() - m_ball_radius - 1, center.y() - m_ball_radius - 1, center.x() + m_ball_radius + 1, center.y() + m_ball_radius + 1);
}

void AltTable::draw_ball(QPainter &painter, const QRect& rect)
{

    if (rect.intersects(ball_rect(m_new_ball_pos))) {
//        if (m_ball_in_play) {
            painter.setBrush(QBrush(Qt::red));
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

    QImage red_box(m_width, m_height, QImage::Format_RGB32);
    red_box.fill(Qt::red);

    painter.drawImage(0, 0, red_box);
    painter.drawImage(0, 0, m_image);
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
}

void AltTable::mouseReleaseEvent(QMouseEvent *e)
{
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
}
