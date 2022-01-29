
#ifndef _MORPH_ELEMENT_H_
#define _MORPH_ELEMENT_H_

#include "float3.h"

class MorphElement
{
public:
    static const int MORPH_NONE = 0;
    static const int MORPH_BRICK = 1;
    static const int MORPH_LEDGE = 2;
    static const int MORPH_WINDOW = 3;
    static const int MORPH_DOOR = 4;
    static const int MORPH_ITEMS = 4;

public:
    MorphElement();
    ~MorphElement();
    void constrain(int kind, Float3 position, int span, int orientation, int clearance);
    Float3 pos() const;
    int span() const;
    int height() const;
    int orientation() const;
    int hgrilles() const;
    int vgrilles() const;
    int kind() const;
    float clearance() const;
    void morph();
    void increase_height();
    void decrease_height();
    void increase_vgrilles();
    void decrease_vgrilles();
    void increase_hgrilles();
    void decrease_hgrilles();
    void flip();

private:
    int m_kind;
    Float3 m_position;
    int m_span;
    int m_height;
    int m_orientation;
    int m_hgrilles;
    int m_vgrilles;
    int m_clearance;
};

#endif // _MORPH_ELEMENT_H_
