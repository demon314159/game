
#ifndef _IMAGE_SET_H_
#define _IMAGE_SET_H_

#include "animated_image.h"

class ImageSet
{
    static const int TARGETS = 7;
    static const int OUTS = 3;
    static const int DIGITS = 10;
public:
    ImageSet();
    ~ImageSet();
    void difference(AnimatedImage&, int& x1, int& y1, int& x2, int& y2);

    QImage m_baseline;
    AnimatedImage m_bat;
    AnimatedImage m_pitch;
    AnimatedImage m_target[TARGETS];
    AnimatedImage m_outs[OUTS];
    AnimatedImage m_left_digit[DIGITS];
    AnimatedImage m_middle_digit[DIGITS];
    AnimatedImage m_right_digit[DIGITS];
};

#endif // _IMAGE_SET_H_
