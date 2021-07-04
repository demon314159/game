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
    , m_velocity(0.0, 0.0, 0.0)
    , m_stopped(false)
    , m_launch_position(QVector3D(0.0, 0.0, 0.0))
    , m_hit_position(QVector3D(0.0, 0.0, 0.0))
    , m_position(QVector3D(0.0, 0.0, 4.0))
    , m_last_position(QVector3D(0.0, 0.0, 4.0))
{
}

Ball::~Ball()
{
}

void Ball::launch(const QVector3D& launch_position)
{
    m_launch_position = launch_position;
    m_velocity = QVector3D(0.0, 0.0, launch_velocity);
    m_t_launch = QTime::currentTime().msecsSinceStartOfDay();
}

void Ball::hit(const QVector3D& bat_pivot_position)
{
    if (m_t_launch > 0) {
        int t_hit = QTime::currentTime().msecsSinceStartOfDay();
        int tdiff = t_hit - m_t_launch;
        float dt = ((float) tdiff) / 1000.0;
        m_hit_position = m_launch_position + dt * m_velocity;
        float dx = bat_pivot_position.x();
        float dz = bat_pivot_position.z() - m_hit_position.z();
        float theta = atanf(dz / dx);
        m_velocity = QVector3D(hit_velocity * sin(theta), 0.0, -hit_velocity * cos(theta));
        m_t_hit = t_hit;
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

bool Ball::reflect(QVector3D& pos)
{
    if (pos.x() < left_border(pos.z())) {
        m_velocity.setX(-m_velocity.x());
        float delta = m_hit_position.x() - left_border(pos.z());
        m_hit_position.setX(m_hit_position.x() - 2.0 * delta);
        return true;
    }
    if (pos.x() > right_border(pos.z())) {
        m_velocity.setX(-m_velocity.x());
        float delta = right_border(pos.z()) - m_hit_position.x();
        m_hit_position.setX(m_hit_position.x() + 2.0 * delta);
        return true;
    }
    return false;
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
}

QVector3D Ball::position_now(int t_now)
{
    QVector3D res;

    if (m_t_launch > 0) {
        if (m_t_hit > 0) {
            int tdiff = t_now - m_t_hit;
            float dt = ((float) tdiff) / 1000.0;
            res = m_hit_position + dt * m_velocity;
            if (reflect(res)) {
                res = m_hit_position + dt * m_velocity;
            }
            check_limits(res);
        } else {
            int tdiff = t_now - m_t_launch;
            float dt = ((float) tdiff) / 1000.0;
            res = m_launch_position + dt * m_velocity;
            check_limits(res);
        }
    } else {
        res = m_position;
    }
    return res;
}


