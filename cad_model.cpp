//
// cad_model.cpp
//
#include "cad_model.h"
#include <math.h>
#include "matrix3x3.h"

#define notVERBOSE

CadModel::CadModel()
    : m_facet_count(0)
    , m_facet(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel()\n");
#endif
}

CadModel::CadModel(const CadModel& cad_model, float x, float y, float z)
    : m_facet_count(0)
    , m_facet(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(CadModel) offset = (%8.6f, %8.6f, %8.6f)\n", x, y, z);
#endif
    m_facet_count = cad_model.facets();
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        Float3 offset = {x, y, z};
        for (int i = 0; i < m_facet_count; i++) {
            m_facet[i].animation_id = cad_model.facet_animation_id(i);
            m_facet[i].v1 = translate(cad_model.facet_v1(i), offset);
            m_facet[i].v2 = translate(cad_model.facet_v2(i), offset);
            m_facet[i].v3 = translate(cad_model.facet_v3(i), offset);
            m_facet[i].color = cad_model.facet_color(i);
        }
    }
}

CadModel::CadModel(const Shape& s, const PaintCan& paint_can, float animation_id)
    : m_facet_count(0)
    , m_facet(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(shape), paint = (%8.6f, %8.6f, %8.6f), animation_id = %7.3f\n",
           paint_can.ambient_color().v1, paint_can.ambient_color().v2, paint_can.ambient_color().v3,
           animation_id);
#endif
    m_facet_count = s.facets();
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_facet[i].animation_id = animation_id;
            m_facet[i].v1 = s.facet(i).v1;
            m_facet[i].v2 = s.facet(i).v2;
            m_facet[i].v3 = s.facet(i).v3;
            m_facet[i].color = paint_can.ambient_color();
        }
    }
}

CadModel::CadModel(const Shape& s)
    : m_facet_count(0)
    , m_facet(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(shape)\n");
#endif
    m_facet_count = s.facets();
    if (m_facet_count > 0) {
        m_facet = new Facet[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_facet[i].animation_id = s.facet(i).animation_id;
            m_facet[i].v1 = s.facet(i).v1;
            m_facet[i].v2 = s.facet(i).v2;
            m_facet[i].v3 = s.facet(i).v3;
            m_facet[i].color = s.facet(i).color;
        }
    }
}

void CadModel::add(const Shape& s, const PaintCan& paint_can, float animation_id)
{
#ifdef VERBOSE
    printf("CadModel::add(shape) paint = (%8.6f, %8.6f, %8.6f) animation_id = %7.3f\n",
           paint_can.ambient_color().v1, paint_can.ambient_color().v2, paint_can.ambient_color().v3,
           animation_id);
#endif
    int added_facet_count = s.facets();
    if (added_facet_count > 0) {
        Facet* tfacet = m_facet;
        m_facet = new Facet[m_facet_count + added_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_facet[i] = tfacet[i];
        }
        for (int i = 0; i < added_facet_count; i++) {
            m_facet[m_facet_count + i].animation_id = animation_id;
            m_facet[m_facet_count + i].v1 = s.facet(i).v1;
            m_facet[m_facet_count + i].v2 = s.facet(i).v2;
            m_facet[m_facet_count + i].v3 = s.facet(i).v3;
            m_facet[m_facet_count + i].color = paint_can.ambient_color();
        }
        m_facet_count += added_facet_count;
        delete [] tfacet;
    }
}

void CadModel::add(const CadModel& cad_model, float x, float y, float z)
{
#ifdef VERBOSE
    printf("CadModel::add(CadModel) offset = (%8.6f, %8.6f, %8.6f)\n", x, y, z);
#endif
    int added_facet_count = cad_model.facets();
    if (added_facet_count > 0) {
        Facet* tfacet = m_facet;
        m_facet = new Facet[m_facet_count + added_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_facet[i] = tfacet[i];
        }
        Float3 offset = {x, y, z};
        for (int i = 0; i < added_facet_count; i++) {
            m_facet[m_facet_count + i].animation_id = cad_model.facet_animation_id(i);
            m_facet[m_facet_count + i].v1 = translate(cad_model.facet_v1(i), offset);
            m_facet[m_facet_count + i].v2 = translate(cad_model.facet_v2(i), offset);
            m_facet[m_facet_count + i].v3 = translate(cad_model.facet_v3(i), offset);
            m_facet[m_facet_count + i].color = cad_model.facet_color(i);
        }
        m_facet_count += added_facet_count;
        delete [] tfacet;
    }
}

int CadModel::facets() const
{
    return m_facet_count;
}

Facet CadModel::facet(int ix) const
{
    return m_facet[ix];
}

float CadModel::facet_animation_id(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet[facet_ix].animation_id;
    else
        return 0.0;
}

Float3 CadModel::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet[facet_ix].v1;
    else
        return {0.0, 0.0, 0.0};
}

Float3 CadModel::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet[facet_ix].v2;
    else
        return {0.0, 0.0, 0.0};
}

Float3 CadModel::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet[facet_ix].v3;
    else
        return {0.0, 0.0, 0.0};
}

Float3 CadModel::facet_color(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet[facet_ix].color;
    else
        return Float3{.0, 0.0, 0.0};
}

Float3 CadModel::facet_normal(int facet_ix) const
{
    Float3 p1, p2, p3;
    p1 = facet_v1(facet_ix);
    p2 = facet_v2(facet_ix);
    p3 = facet_v3(facet_ix);
    Float3 va, vb;
    va.v1 = p2.v1 - p1.v1;
    va.v2 = p2.v2 - p1.v2;
    va.v3 = p2.v3 - p1.v3;
    vb.v1 = p3.v1 - p1.v1;
    vb.v2 = p3.v2 - p1.v2;
    vb.v3 = p3.v3 - p1.v3;
    Float3 xp;
    xp.v1 = va.v2 * vb.v3 - vb.v2 * va.v3;
    xp.v2 = vb.v1 * va.v3 - va.v1 * vb.v3;
    xp.v3 = va.v1 * vb.v2 - vb.v1 * va.v2;
    return xp;
}

Float3 CadModel::translate(const Float3& v, const Float3& offset) const
{
    Float3 t;
    t.v1 = v.v1 + offset.v1;
    t.v2 = v.v2 + offset.v2;
    t.v3 = v.v3 + offset.v3;
    return t;
}

Facet CadModel::translate(const Facet& f, const Float3& offset) const
{
    Facet t;
    t = f;
    t.v1 = translate(t.v1, offset);
    t.v2 = translate(t.v2, offset);
    t.v3 = translate(t.v3, offset);
    return t;
}

void CadModel::rotate_ax(float angle)
{
    Matrix3x3 rm;
    rm.unity();
    rm.rotate_ax(angle);
    Matrix3x3 m;
    for (int i = 0; i < m_facet_count; i++) {
        m.set_col(0, m_facet[i].v1);
        m.set_col(1, m_facet[i].v2);
        m.set_col(2, m_facet[i].v3);
        m = rm * m;
        m_facet[i].v1 = m.get_col(0);
        m_facet[i].v2 = m.get_col(1);
        m_facet[i].v3 = m.get_col(2);
    }
}

void CadModel::rotate_ay(float angle)
{
    Matrix3x3 rm;
    rm.unity();
    rm.rotate_ay(angle);
    Matrix3x3 m;
    for (int i = 0; i < m_facet_count; i++) {
        m.set_col(0, m_facet[i].v1);
        m.set_col(1, m_facet[i].v2);
        m.set_col(2, m_facet[i].v3);
        m = rm * m;
        m_facet[i].v1 = m.get_col(0);
        m_facet[i].v2 = m.get_col(1);
        m_facet[i].v3 = m.get_col(2);
    }
}

void CadModel::rotate_az(float angle)
{
    Matrix3x3 rm;
    rm.unity();
    rm.rotate_az(angle);
    Matrix3x3 m;
    for (int i = 0; i < m_facet_count; i++) {
        m.set_col(0, m_facet[i].v1);
        m.set_col(1, m_facet[i].v2);
        m.set_col(2, m_facet[i].v3);
        m = rm * m;
        m_facet[i].v1 = m.get_col(0);
        m_facet[i].v2 = m.get_col(1);
        m_facet[i].v3 = m.get_col(2);
    }
}

void CadModel::magnify(float factor)
{
    for (int i = 0; i < m_facet_count; i++) {
        m_facet[i].v1.v1 *= factor;
        m_facet[i].v1.v2 *= factor;
        m_facet[i].v1.v3 *= factor;
        m_facet[i].v2.v1 *= factor;
        m_facet[i].v2.v2 *= factor;
        m_facet[i].v2.v3 *= factor;
        m_facet[i].v3.v1 *= factor;
        m_facet[i].v3.v2 *= factor;
        m_facet[i].v3.v3 *= factor;
    }
}

CadModel::~CadModel()
{
#ifdef VERBOSE
    printf("~CadModel::CadModel()\n");
#endif
    if (m_facet != NULL)
        delete [] m_facet;
}

BoundingBox CadModel::bounding_box() const
{
    BoundingBox bb;
    if (m_facet_count == 0) {
        bb.vmin.v1 = -0.5;
        bb.vmin.v2 = 0.0;
        bb.vmin.v3 = -0.5;
        bb.vmax.v1 = 0.5;
        bb.vmax.v2 = 1.0;
        bb.vmax.v3 = 0.5;
        return bb;
    }
    bb.vmin = facet_v1(0);
    bb.vmax = facet_v1(0);
    for (int i = 0; i < m_facet_count; i++) {
        Float3 v = facet_v1(i);
        bb.vmin.v1 = fmin(bb.vmin.v1, v.v1);
        bb.vmin.v2 = fmin(bb.vmin.v2, v.v2);
        bb.vmin.v3 = fmin(bb.vmin.v3, v.v3);
        bb.vmax.v1 = fmax(bb.vmax.v1, v.v1);
        bb.vmax.v2 = fmax(bb.vmax.v2, v.v2);
        bb.vmax.v3 = fmax(bb.vmax.v3, v.v3);
        v = facet_v2(i);
        bb.vmin.v1 = fmin(bb.vmin.v1, v.v1);
        bb.vmin.v2 = fmin(bb.vmin.v2, v.v2);
        bb.vmin.v3 = fmin(bb.vmin.v3, v.v3);
        bb.vmax.v1 = fmax(bb.vmax.v1, v.v1);
        bb.vmax.v2 = fmax(bb.vmax.v2, v.v2);
        bb.vmax.v3 = fmax(bb.vmax.v3, v.v3);
        v = facet_v3(i);
        bb.vmin.v1 = fmin(bb.vmin.v1, v.v1);
        bb.vmin.v2 = fmin(bb.vmin.v2, v.v2);
        bb.vmin.v3 = fmin(bb.vmin.v3, v.v3);
        bb.vmax.v1 = fmax(bb.vmax.v1, v.v1);
        bb.vmax.v2 = fmax(bb.vmax.v2, v.v2);
        bb.vmax.v3 = fmax(bb.vmax.v3, v.v3);
    }
    return bb;
}


