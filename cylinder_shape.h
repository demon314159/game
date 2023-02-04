
#ifndef _CYLINDER_SHAPE_H_
#define _CYLINDER_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class CylinderShape: public Shape
{
public:
    CylinderShape(float radius, float height, float upper_bevel = 0.0, float lower_bevel = 0.0);
    virtual ~CylinderShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_height;
    float m_upper_bevel;
    float m_lower_bevel;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _CYLINDER_SHAPE_
