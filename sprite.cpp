//
// sprite.cpp
//
#include "sprite.h"

Sprite::Sprite(const QString& file_name, float radius)
    :m_radius(radius)
{
    m_set.load(file_name);
}

float Sprite::radius() const
{
    return m_radius;
}

QImage Sprite::copy(int x, int y, int w, int h) const
{
    return m_set.copy(x, y, w, h);
}
