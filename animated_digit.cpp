
#include "animated_digit.h"

AnimatedDigit::AnimatedDigit()
    : m_x(0)
    , m_y(0)
{
}

AnimatedDigit::AnimatedDigit(int x, int y, const QImage (&image)[10])
    : m_x(x)
    , m_y(y)
    , m_image(image)
{
}

AnimatedDigit::~AnimatedDigit()
{
}

QRect AnimatedDigit::rect() const
{
    QRect r(m_x, m_y, m_image[0].width(), m_image[0].height());
    return r;
}


