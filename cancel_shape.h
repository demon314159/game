
#ifndef _CANCEL_SHAPE_H_
#define _CANCEL_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class CancelShape: public Shape
{
public:
    CancelShape(float width);
    virtual ~CancelShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_width;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _CANCEL_SHAPE_