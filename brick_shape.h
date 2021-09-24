
#ifndef _BRICK_SHAPE_H_
#define _BRICK_SHAPE_H_

#include "float3.h"

class BrickShape
{
public:
    BrickShape(float dimx, float dimy, float dimz, float dimb);
    ~BrickShape();
    int facet_count() const;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    int m_facet_count;
    bool m_count_mode;

    void define_shape();
    void add_face(int v1, int v2, int v3, bool flip = false);
    void add_face(int v1, int v2, int v3, int v4, bool flip = false);
    void add_vertex(int v);
};

#endif // _BRICK_SHAPE_
