//
// shape_set.h
//
#if !defined(_SHAPE_SET_H_)
#define _SHAPE_SET_H_

#define MAX_SHAPES 36

#include "shape.h"

class ShapeSet
{
public:
    ShapeSet(void);
    ~ShapeSet();
    int tiles(int shape_id) const;
    int posh(int shape_id, int tix, int orientation) const;
    int posv(int shape_id, int tix, int orientation) const;

protected:
    int m_shapes;
    Shape m_list[MAX_SHAPES];

    void add_shape(const Shape& shape);
};

#endif // _SHAPE_SET_H_
