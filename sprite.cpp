//
// sprite.cpp
//
#include "sprite.h"

Sprite::Sprite(const QString& file_name, float radius, const QVector3D& error_vector)
    : m_radius(radius)
    , m_error_vector(error_vector)
{
    m_set.load(file_name);
}

float Sprite::radius() const
{
    return m_radius;
}

QVector3D Sprite::error_vector() const
{
    return m_error_vector;
}

QImage Sprite::copy(int x, int y, int w, int h) const
{
    return m_set.copy(x, y, w, h);
}
