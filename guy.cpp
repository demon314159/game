//
// guy.cpp
//
#include "guy.h"
#include <math.h>
#include <QTime>

Guy::Guy(float left, float right, float back, float front)
    : m_left(left)
    , m_right(right)
    , m_back(back)
    , m_front(front)
{
}

Guy::~Guy()
{
}

QVector3D Guy::position() const
{
    if (m_position <= 1.0) {
        float xc = (m_right + m_left) / 2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(xc + m_position * (m_right - xc), 0.0, m_front + m_position * (yc - m_front));
    } else {
        return QVector3D(m_right, 0.0, m_front);
    }
}

QVector3D Guy::last_position() const
{
    if (m_last_position <= 1.0) {
        float xc = (m_right + m_left)/2.0;
        float yc = (m_front + m_back) / 2.0;
        return QVector3D(xc + m_last_position * (m_right - xc), 0.0, m_front + m_last_position * (yc - m_front));
    } else {
        return QVector3D(m_right, 0.0, m_front);
    }
}

void Guy::update()
{
    m_last_position = m_position;
    m_position = m_position + 0.05;
    if (m_position >= 1.0)
        m_position = 0.0;
}


