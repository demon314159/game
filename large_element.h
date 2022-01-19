
#ifndef _LARGE_ELEMENT_H_
#define _LARGE_ELEMENT_H_

#include "float3.h"

class LargeElement
{
public:
    LargeElement();
    ~LargeElement();
    void constrain(Float3 position, int span, int orientation, bool gap_below);
    Float3 pos() const;
    int span() const;
    int height() const;
    int orientation() const;
    int hgrilles() const;
    int vgrilles() const;
    bool is_door() const;
    bool is_gap_below() const;
    void increase_height();
    void decrease_height();
    void increase_vgrilles();
    void decrease_vgrilles();
    void increase_hgrilles();
    void decrease_hgrilles();
    void flip();

private:
    Float3 m_position;
    int m_span;
    int m_height;
    int m_orientation;
    int m_hgrilles;
    int m_vgrilles;
    bool m_door_flag;
    bool m_gap_below;
};

#endif // _LARGE_ELEMENT_H_
