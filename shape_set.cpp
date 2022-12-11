//
// shape_set.cpp
//
#include "shape_set.h"

ShapeSet::ShapeSet(void)
    : m_shapes(0)
{
    add_shape(Shape().t(0, 0));                                            // shape_id = 0
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(0, 5));    // shape_id = 1
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 4));    // shape_id = 2
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 3));    // shape_id = 3
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(0, 4).t(1, 2));    // shape_id = 4
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 5
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(1, 4));    // shape_id = 6
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(1, 4));    // shape_id = 7
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(1, 3));    // shape_id = 8
    add_shape(Shape().t(0, 0).t(1, 0).t(1, 1).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 9
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 3).t(1, 3));   // shape_id = 10
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 3).t(2, 3));    // shape_id = 11
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(1, 2));    // shape_id = 12
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 3));    // shape_id = 13
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 1).t(1, 2).t(2, 2).t(2, 3));    // shape_id = 14
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 2));    // shape_id = 15
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 2));   // shape_id = 16
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 1).t(1, 3));    // shape_id = 17
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(1, 3).t(2, 2));    // shape_id = 18
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 3));    // shape_id = 19
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(1, 2).t(1, 3));    // shape_id = 20
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(2, 1).t(2, 2));    // shape_id = 21
    add_shape(Shape().t(0, 0).t(0, 1).t(1, 0).t(1, 1).t(1, 2).t(2, 1));    // shape_id = 22
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 0).t(1, 3));    // shape_id = 23
    add_shape(Shape().t(0, 0).t(0, 1).t(-1, 1).t(-1, 2).t(1, 1).t(1, 2));  // shape_id = 24
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 2).t(2, 2).t(2, 1));    // shape_id = 25
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 1).t(2, 0));    // shape_id = 26
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // shape_id = 27
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(1, 2).t(2, 2));    // shape_id = 28
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 0).t(1, 2).t(1, 3));    // shape_id = 29
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(1, 1).t(2, 1).t(2, 2));    // shape_id = 30
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 1).t(1, 2));   // shape_id = 31
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 2).t(1, 2).t(1, 3));   // shape_id = 32
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 2).t(1, 3));   // shape_id = 33
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(0, 3).t(-1, 1).t(1, 2));   // shape_id = 34
    add_shape(Shape().t(0, 0).t(0, 1).t(0, 2).t(-1, 1).t(1, 2).t(1, 3));   // shape_id = 35
}

ShapeSet::~ShapeSet()
{
}

void ShapeSet::add_shape(const Shape& shape)
{
    if (m_shapes < MAX_SHAPES) {
        m_list[m_shapes] = shape;
        ++m_shapes;
    }
}


