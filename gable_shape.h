
#ifndef _GABLE_SHAPE_H_
#define _GABLE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class GableShape: public Shape
{
public:
    GableShape(float dimx, float dimy, float dimz, float dimb);
    virtual ~GableShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(int v1, int v2, int v3, bool flip = false);
    void add_face(int v1, int v2, int v3, int v4, bool flip = false);
    Float3 decode_vertex(int v);
};

#endif // _GABLE_SHAPE_
