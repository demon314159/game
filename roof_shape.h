
#ifndef _ROOF_SHAPE_H_
#define _ROOF_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class RoofShape: public Shape
{
public:
    RoofShape(float dimx, float dimy, float dimz, float dimb, bool part1);
    virtual ~RoofShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    bool m_part1;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _ROOF_SHAPE_
