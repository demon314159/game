
#include "animated_image.h"

AnimatedImage::AnimatedImage()
    : m_x(0)
    , m_y(0)
{
}

AnimatedImage::AnimatedImage(int x, int y, const QImage& on_image, const QImage& off_image)
    : m_x(x)
    , m_y(y)
    , m_on_image(on_image)
    , m_off_image(off_image)
{
}

AnimatedImage::~AnimatedImage()
{
}

QRect AnimatedImage::rect() const
{
    QRect r(m_x, m_y, m_on_image.width(), m_on_image.height());
    return r;
}


