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

QVector3D Guy::position(int base) const
{
    if (base == 1)
        return QVector3D(m_right, 0.0, (m_front + m_back) / 2.0);
    if (base == 2)
        return QVector3D((m_right + m_left) / 2.0, 0.0, m_back);
    if (base == 3)
        return QVector3D(m_left, 0.0, (m_front + m_back) / 2.0);
    return QVector3D((m_right + m_left) / 2.0, 0.0, m_front);
}



