
#ifndef _MOUSE_VECTOR_SHAPE_H_
#define _MOUSE_VECTOR_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"
#include "mouse_vector.h"

class MouseVectorShape: public Shape
{
public:
    MouseVectorShape(MouseVector mv, float t0, float t1);
    virtual ~MouseVectorShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    Float3 m_pt0;
    Float3 m_pt1;
    float m_dimb;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(int v1, int v2, int v3, bool flip = false);
    void add_face(int v1, int v2, int v3, int v4, bool flip = false);
    Float3 decode_vertex(int v);
};

#endif // _CUBE_SHAPE_
