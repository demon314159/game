
#ifndef _QUARTER_BRICK_SHAPE_H_
#define _QUARTER_BRICK_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"
#include <QMatrix4x4>

class QuarterBrickShape: public Shape
{
public:
    QuarterBrickShape(float dimx, float dimy, float dimz, float dimb, int orientation);
    virtual ~QuarterBrickShape();
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

private:
    void define_shape();
    void add_face(int v1, int v2, int v3, bool flip = false);
    void add_face(int v1, int v2, int v3, int v4, bool flip = false);
    Float3 decode_vertex(int v);
    void rotate_ay(float angle);
    void rotate_vertex(Float3& vertex, const QMatrix4x4& matrix);
};

#endif // _QUARTER_BRICK_SHAPE_
