
#ifndef _RING_SHAPE_H_
#define _RING_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class RingShape: public Shape
{
public:
    RingShape(float radius_o, float radius_i, float height);
    virtual ~RingShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius_o;
    float m_radius_i;
    float m_height;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _RING_SHAPE_
