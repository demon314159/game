
#ifndef _ANIMATED_IMAGE_H_
#define _ANIMATED_IMAGE_H_

#include <QImage>

class AnimatedImage
{
public:
    AnimatedImage();
    AnimatedImage(int x, int y, const QImage& image);
    ~AnimatedImage();
    QRect rect() const;

    int m_x;
    int m_y;
    QImage m_image;
};

#endif // _ANIMATED_IMAGE_H_
