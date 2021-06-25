
#include "animated_image.h"

AnimatedImage::AnimatedImage()
    : m_x(0)
    , m_y(0)
{
}

AnimatedImage::AnimatedImage(int x, int y, const QImage& image)
    : m_x(x)
    , m_y(y)
    , m_image(image)
{
}

AnimatedImage::~AnimatedImage()
{
}


