//
// ball.cpp
//
#include "ball.h"
#include <math.h>
#include <QTime>

Ball::Ball(float back_width, float front_width, float back, float front)
    : m_back_width(back_width)
    , m_front_width(front_width)
    , m_back(back)
    , m_front(front)
    , m_t_launch(0)
    , m_t_hit(0)
    , m_stopped(false)
    , m_launch_position(QVector3D(0.0, 0.0, 0.0))
    , m_bat_pivot_position(QVector3D(0.0, 0.0, 0.0))
    , m_position(QVector3D(0.0, 0.0, 4.0))
{
}

Ball::~Ball()
{
}

void Ball::launch(const QVector3D& launch_position)
{
    m_t_launch = QTime::currentTime().msecsSinceStartOfDay();
    m_launch_position = launch_position;
}

void Ball::hit(const QVector3D& bat_pivot_position)
{
    if (m_t_launch > 0) {
        m_t_hit = QTime::currentTime().msecsSinceStartOfDay();
        m_bat_pivot_position = bat_pivot_position;
    }
}

void Ball::stop()
{
    m_t_launch = 0;
    m_t_hit = 0;
    m_stopped = true;
}

void Ball::reset()
{
    stop();
    m_stopped = false;
    m_position = QVector3D(0.0, 0.0, 4.0);
}

void Ball::update()
{
    m_last_position = m_position;
    m_position = position_now(QTime::currentTime().msecsSinceStartOfDay());
}

bool Ball::in_play() const
{
    return m_t_launch > 0;
}

bool Ball::stopped() const
{
    return m_stopped;
}

QVector3D Ball::position() const
{
    return m_position;
}

QVector3D Ball::last_position() const
{
    return m_last_position;
}

float Ball::left_border(float z) const
{
    float x1 = -m_back_width / 2.0;
    float z1 = m_back;
    float x2 = -m_front_width / 2.0;
    float z2 = m_front;
    return x1 + (z - z1) * (x2 - x1) / (z2 - z1);
}

float Ball::right_border(float z) const
{
    float x1 = m_back_width / 2.0;
    float z1 = m_back;
    float x2 = m_front_width / 2.0;
    float z2 = m_front;
    return x1 + (z - z1) * (x2 - x1) / (z2 - z1);
}

void Ball::check_limits(QVector3D& pos)
{
    if (pos.z() < m_back) {
        pos.setZ(m_back);
        stop();
        return;
    }
    if (pos.z() > m_front) {
        pos.setZ(m_front);
        stop();
        return;
    }
    if (pos.x() < left_border(pos.z())) {
        pos.setX(left_border(pos.z()));
        stop();
        return;
    }
    if (pos.x() > right_border(pos.z())) {
        pos.setX(right_border(pos.z()));
        stop();
        return;
    }
}

QVector3D Ball::position_now(int t_now)
{
    QVector3D res;

    if (m_t_launch > 0) {
        if (m_t_hit > 0) {
            int tdiff = m_t_hit - m_t_launch;
            QVector3D hit_pos = m_launch_position + QVector3D(0.0, 0.0, velocity * (float) tdiff / 1000.0);
            float dx = m_bat_pivot_position.x();
            float dz = m_bat_pivot_position.z() - hit_pos.z();
            float theta = atanf(dz / dx);
            float vx = hit_velocity * sin(theta);
            float vz = hit_velocity * cos(theta);
            tdiff = t_now - m_t_hit;
            res = hit_pos + QVector3D(vx * (float) tdiff / 1000.0, 0.0, - vz * (float) tdiff / 1000.0);
            check_limits(res);
        } else {
            int tdiff = t_now - m_t_launch;
            res = m_launch_position + QVector3D(0.0, 0.0, velocity * (float) tdiff / 1000.0);
            check_limits(res);
        }
    } else {
        res = m_position;
    }
    return res;
}


