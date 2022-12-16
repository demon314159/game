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
    bool shape_contained(int shape_id, int orientation, int ph, int pv, int dimh, int dimv) const;
    bool shape_collision(int shape_id1, int orientation1, int ph1, int pv1, int shape_id2, int orientation2, int ph2, int pv2) const;
    bool tile_at(int shape_id, int orientation, int x, int y) const;

protected:
    int m_shapes;
    Shape m_list[MAX_SHAPES];

    void add_shape(const Shape& shape);
};

#endif // _SHAPE_SET_H_
