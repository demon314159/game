
#ifndef _MORPH_SHAPE_H_
#define _MORPH_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class MorphShape: public Shape
{
public:
    MorphShape(int spikes, float width, float separation);
    virtual ~MorphShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    int m_spikes;
    float m_width;
    float m_separation;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _MORPH_SHAPE_
