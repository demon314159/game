
#ifndef _TRACK_SHAPE_H_
#define _TRACK_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TrackShape: public Shape
{
public:
    TrackShape(float dimx, float dimy, float dimz, float dimb, float dimsw, float dimsh, float dimrw, float dimts);
    virtual ~TrackShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_dimb;
    float m_dimsw;
    float m_dimsh;
    float m_dimrw;
    float m_dimts;
    bool m_count_mode;
    int m_facet_count;
    Facet *m_facet;
    void define_shape();
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TRACK_SHAPE_
