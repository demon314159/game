//
// guy.cpp
//
#include "guy.h"
#include <math.h>
#include <QTime>

Guy::Guy(float left, float right, float back, float front)
    : Sprite(":/guy_set.png", GUY_RADIUS)
    , m_left(left)
    , m_right(right)
    , m_back(back)
    , m_front(front)
    , m_stop_position(0.0)
    , m_t_launch(0.0)
    , m_position(0.0)
    , m_last_position(0.0)
{
}

Guy::~Guy()
{
}

QVector3D Guy::calc_position(float pos) const
{
    if (pos <= 1.0) {
        float xc = (m_right + m_left)/2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(xc + pos * (m_right - xc), GUY_RADIUS, m_front + pos * (yc - m_front));
    } else if (pos <= 2.0) {
        float xc = (m_right + m_left)/2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(m_right + (pos - 1.0) * (xc - m_right), GUY_RADIUS, yc + (pos - 1.0) * (m_back - yc));
    } else if (pos <= 3.0) {
        float xc = (m_right + m_left)/2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(xc + (pos - 2.0) * (m_left - xc), GUY_RADIUS, m_back + (pos - 2.0) * (yc - m_back));
    } else if (pos <= 4.0) {
        float xc = (m_right + m_left)/2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(m_left + (pos - 3.0) * (xc - m_left), GUY_RADIUS, yc + (pos - 3.0) * (m_front - yc));
    } else {
        return QVector3D(m_right, GUY_RADIUS, m_front);
    }
}

QVector3D Guy::position() const
{
    return calc_position(m_position);
}

QVector3D Guy::last_position() const
{
    return calc_position(m_last_position);
}

void Guy::launch(float start_position, float stop_position)
{
    m_last_position = m_position;
    m_position = start_position;
    m_stop_position = stop_position;
}

bool Guy::in_play() const
{
    return m_position > 0.0 && m_position < 4.0;
}

void Guy::update()
{
    if (m_position < m_stop_position) {
      m_last_position = m_position;
      m_position = fmin(m_position + 0.05, m_stop_position);
   }
}


