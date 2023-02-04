
#ifndef _RING_SHAPE_H_
#define _RING_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class RingShape: public Shape
{
public:
    RingShape(float radius_o, float radius_i, float height, float upper_bevel_o = 0.0, float upper_bevel_i = 0.0, float lower_bevel_o = 0.0, float lower_bevel_i = 0.0);
    virtual ~RingShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius_o;
    float m_radius_i;
    float m_height;
    float m_upper_bevel_o;
    float m_upper_bevel_i;
    float m_lower_bevel_o;
    float m_lower_bevel_i;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _RING_SHAPE_
