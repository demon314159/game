
#ifndef _ANIMATED_IMAGE_H_
#define _ANIMATED_IMAGE_H_

#include <QImage>

class AnimatedImage
{
public:
    AnimatedImage();
    AnimatedImage(int x, int y, const QImage& on_image, const QImage& off_image);
    ~AnimatedImage();
    QRect rect() const;

    int m_x;
    int m_y;
    QImage m_on_image;
    QImage m_off_image;
};

#endif // _ANIMATED_IMAGE_H_
