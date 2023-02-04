
#ifndef _CAR_SHAPE_H_
#define _CAR_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class CarShape: public Shape
{
public:
    CarShape(float width, float length);
    virtual ~CarShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_width;
    float m_length;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _CAR_SHAPE_
