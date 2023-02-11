
#ifndef _CURVE_SHAPE_H_
#define _CURVE_SHAPE_H_

#include "shape.h"
#include "curve.h"
#include "float3.h"
#include "facet.h"

class CurveShape: public Shape
{
public:
    CurveShape(const Curve& c1, float z1, const Curve& c2, float z2);
    CurveShape(const Curve& c1, float z1, bool flip = false);
    virtual ~CurveShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape(const Curve& c1, float z1, const Curve& c2, float z2);
    void define_shape(const Curve& c1, float z1, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _CURVE_SHAPE_
