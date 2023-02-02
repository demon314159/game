
#ifndef _TRACK_SHAPE_H_
#define _TRACK_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TrackShape: public Shape
{
public:
    TrackShape(int lanes, float length);
    virtual ~TrackShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    int m_lanes;
    float m_length;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TRACK_SHAPE_
