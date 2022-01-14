
#ifndef _ARROW_SHAPE_H_
#define _ARROW_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class ArrowShape: public Shape
{
public:
    static const int ARROW_UP = 0;
    static const int ARROW_LEFT = 1;
    static const int ARROW_DOWN = 2;
    static const int ARROW_RIGHT = 3;

    ArrowShape(float length, float width, int orientation);
    virtual ~ArrowShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_length;
    float m_width;
    float m_orientation;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4);
};

#endif // _ARROW_SHAPE_
