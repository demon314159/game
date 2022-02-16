
#ifndef _MORPH_SHAPE_H_
#define _MORPH_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class MorphShape: public Shape
{
public:
    MorphShape(float width);
    virtual ~MorphShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_width;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void define_arrow_shape(float degrees);
    void add_face(float degrees, Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(float degrees, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    Float3 rotate(Float3 v, float degrees);
};

#endif // _MORPH_SHAPE_
