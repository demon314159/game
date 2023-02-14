
#ifndef _BOX_SHAPE_H_
#define _BOX_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class BoxShape: public Shape
{
public:
    BoxShape(Float3 pl0, Float3 pl1, Float3 pl2, Float3 pl3, Float3 pu0, Float3 pu1, Float3 pu2, Float3 pu3);
    virtual ~BoxShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    Float3 m_pl0;
    Float3 m_pl1;
    Float3 m_pl2;
    Float3 m_pl3;
    Float3 m_pu0;
    Float3 m_pu1;
    Float3 m_pu2;
    Float3 m_pu3;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _BOX_SHAPE_
