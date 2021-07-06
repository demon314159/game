
#ifndef _ANIMATED_DIGIT_H_
#define _ANIMATED_DIGIT_H_

#include <QImage>

class AnimatedDigit
{
public:
    AnimatedDigit();
    AnimatedDigit(int x, int y, const QImage (&image)[10]);
    ~AnimatedDigit();
    QRect rect() const;

    int m_x;
    int m_y;
    QImage m_image[10];
};

#endif // _ANIMATED_DIGIT_H_
