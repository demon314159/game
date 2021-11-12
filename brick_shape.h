
#ifndef _BRICK_SHAPE_H_
#define _BRICK_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class BrickShape: public Shape
{
public:
    BrickShape(float dimx, float dimy, float dimz, float dimb);
    virtual ~BrickShape();
    int facets() const override;
    facet get_facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    bool m_count_mode;
    int m_facet_count;
    facet *m_facet;

    void define_shape();
    void add_face(int v1, int v2, int v3, bool flip = false);
    void add_face(int v1, int v2, int v3, int v4, bool flip = false);
    float3 decode_vertex(int v);
};

#endif // _BRICK_SHAPE_
