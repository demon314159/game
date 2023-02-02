
#include "track_shape.h"
#include "look.h"
#include <cstddef>

TrackShape::TrackShape(float dimx, float dimy, float dimz, float dimb, float dimsw, float dimsh, float dimrw, float dimts)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
    , m_dimsw(dimsw)
    , m_dimsh(dimsh)
    , m_dimrw(dimrw)
    , m_dimts(dimts)
    , m_count_mode(true)
    , m_facet_count(0)
    , m_facet(NULL)
{
    define_shape();
    m_count_mode = false;
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        m_facet_count = 0;
        define_shape();
    }
}

TrackShape::~TrackShape()
{
    if (m_facet != NULL)
        delete [] m_facet;
}

int TrackShape::facets() const
{
    return m_facet_count;
}

Facet TrackShape::facet(int facet_ix) const
{
    return m_facet[facet_ix];
}

void TrackShape::define_shape()
{
    float x0 = -m_dimx / 2.0;
    float x1 = -m_dimx / 2.0 + m_dimb;
    float x2 = -m_dimts / 2.0 - m_dimsw / 2.0;
    float x3 = -m_dimts / 2.0 - m_dimsw / 2.0 + m_dimrw;
    float x4 = -m_dimts / 2.0 + m_dimsw / 2.0 - m_dimrw;
    float x5 = -m_dimts / 2.0 + m_dimsw / 2.0;
    float x6 = m_dimts / 2.0 - m_dimsw / 2.0;
    float x7 = m_dimts / 2.0 - m_dimsw / 2.0 + m_dimrw;
    float x8 = m_dimts / 2.0 + m_dimsw / 2.0 - m_dimrw;
    float x9 = m_dimts / 2.0 + m_dimsw / 2.0;
    float x10 = m_dimx / 2.0 - m_dimb;
    float x11 = m_dimx / 2.0;

    float dy = m_dimy;
    float dz = m_dimz;
    float db = m_dimb;
    float sh = m_dimsh;

    Float3 tp = Look::track_paint().ambient_color();
    Float3 sp = Look::slot_paint().ambient_color();
    Float3 rp = Look::rail_paint().ambient_color();

    add_face(0.0, tp, {x0, -dy, dz}, {x0, -dy, -dz}, {x0, dy - db, -dz}, {x0, dy - db, dz}, true);
    add_face(0.0, tp, {x0, dy - db, dz}, {x0, dy - db, -dz}, {x1, dy, -dz}, {x1, dy, dz}, true);
    add_face(0.0, tp, {x1, dy, dz}, {x1, dy, -dz}, {x2, dy, -dz}, {x2, dy, dz}, true);


    add_face(1.0, rp, {x2, dy, dz}, {x2, dy, -dz}, {x3, dy, -dz}, {x3, dy, dz}, true);
    add_face(0.0, tp, {x3, dy, dz}, {x3, dy, -dz}, {x3, dy - sh, -dz}, {x3, dy - sh, dz}, true);
    add_face(1.0, sp, {x3, dy - sh, dz}, {x3, dy - sh, -dz}, {x4, dy - sh, -dz}, {x4, dy - sh, dz}, true);
    add_face(0.0, tp, {x4, dy - sh, dz}, {x4, dy - sh, -dz}, {x4, dy, -dz}, {x4, dy, dz}, true);
    add_face(1.0, rp, {x4, dy, dz}, {x4, dy, -dz}, {x5, dy, -dz}, {x5, dy, dz}, true);

    add_face(0.0, tp, {x5, dy, dz}, {x5, dy, -dz}, {x6, dy, -dz}, {x6, dy, dz}, true);

    add_face(1.0, rp, {x6, dy, dz}, {x6, dy, -dz}, {x7, dy, -dz}, {x7, dy, dz}, true);
    add_face(0.0, tp, {x7, dy, dz}, {x7, dy, -dz}, {x7, dy - sh, -dz}, {x7, dy - sh, dz}, true);
    add_face(1.0, sp, {x7, dy - sh, dz}, {x7, dy - sh, -dz}, {x8, dy - sh, -dz}, {x8, dy - sh, dz}, true);
    add_face(0.0, tp, {x8, dy - sh, dz}, {x8, dy - sh, -dz}, {x8, dy, -dz}, {x8, dy, dz}, true);
    add_face(1.0, rp, {x8, dy, dz}, {x8, dy, -dz}, {x9, dy, -dz}, {x9, dy, dz}, true);


    add_face(0.0, tp, {x9, dy, dz}, {x9, dy, -dz}, {x10, dy, -dz}, {x10, dy, dz}, true);
    add_face(0.0, tp, {x10, dy, dz}, {x10, dy, -dz}, {x11, dy - db, -dz}, {x11, dy - db, dz}, true);
    add_face(0.0, tp, {x11, dy - db, dz}, {x11, dy - db, -dz}, {x11, -dy, -dz}, {x11, -dy, dz}, true);
}

void TrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip)
{
    add_face(animation_id, color, v1, v2, v3, flip);
    add_face(animation_id, color, v1, v3, v4, flip);
}

void TrackShape::add_face(float animation_id, Float3 color, Float3 v1, Float3 v2, Float3 v3, bool flip)
{
    if (!m_count_mode) {
        m_facet[m_facet_count].animation_id = animation_id;
        m_facet[m_facet_count].color = color;
        if (flip) {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v3;
            m_facet[m_facet_count].v3 = v2;
        } else {
            m_facet[m_facet_count].v1 = v1;
            m_facet[m_facet_count].v2 = v2;
            m_facet[m_facet_count].v3 = v3;
        }
    }
    ++m_facet_count;
}


