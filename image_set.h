
#ifndef _IMAGE_SET_H_
#define _IMAGE_SET_H_

#include "animated_image.h"

class ImageSet
{
public:
    ImageSet();
    ~ImageSet();

    AnimatedImage m_baseline;
    AnimatedImage m_bat;
    AnimatedImage m_pitch;
    AnimatedImage m_target1;
    AnimatedImage m_target2;
    AnimatedImage m_target3;
    AnimatedImage m_target4;
    AnimatedImage m_target5;
    AnimatedImage m_target6;
    AnimatedImage m_target7;
};

#endif // _IMAGE_SET_H_
