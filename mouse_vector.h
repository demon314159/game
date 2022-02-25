
#ifndef _MOUSE_VECTOR_H_
#define _MOUSE_VECTOR_H_

#include "float3.h"

class MouseVector
{
public:
    MouseVector(Float3 origin, Float3 vector);
    ~MouseVector();
    Float3 origin() const;
    Float3 vector() const;
    bool is_on() const;
    bool is_dirty() const;
    void make_clean();
    void make_dirty();
    void set_new_vector(Float3 origin, Float3 vector);
    void translate(Float3 off);

private:
    bool m_is_on;
    bool m_is_dirty;
    Float3 m_origin;
    Float3 m_vector;
};

#endif // _MOUSE_VECTOR_H_
