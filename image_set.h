
#ifndef _IMAGE_SET_H_
#define _IMAGE_SET_H_

#include "animated_image.h"

class ImageSet
{
    static const int TARGETS = 7;
public:
    ImageSet();
    ~ImageSet();
    void difference(AnimatedImage&, int& x1, int& y1, int& x2, int& y2);

    QImage m_baseline;
    AnimatedImage m_bat;
    AnimatedImage m_pitch;
    AnimatedImage m_target[TARGETS];
};

#endif // _IMAGE_SET_H_
