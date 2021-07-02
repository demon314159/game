//
// ball.cpp
//
#include "ball.h"
#include <math.h>
#include <QTime>

Ball::Ball(float left, float front, float right, float back)
    : m_left(left)
    , m_right(right)
    , m_front(front)
    , m_back(back)
    , m_t_launch(0)
    , m_t_hit(0)
    , m_launch_position(QVector3D(0.0, 0.0, 0.0))
    , m_bat_pivot_position(QVector3D(0.0, 0.0, 0.0))
    , m_position(QVector3D(0.0, 0.0, 0.0))
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

QVector3D Ball::position() const
{
    return m_position;
}

QVector3D Ball::last_position() const
{
    return m_last_position;
}

void Ball::check_limits(QVector3D& pos)
{
    if (pos.x() < m_left) {
        pos.setX(m_left);
        stop();
    }
    if (pos.x() > m_right) {
        pos.setX(m_right);
        stop();
    }
    if (pos.z() < m_back) {
        pos.setZ(m_back);
        stop();
    }
    if (pos.z() > m_front) {
        pos.setZ(m_front);
        stop();
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


