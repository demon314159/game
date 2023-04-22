//
// cad_model.cpp
//
#include "cad_model.h"
#include <math.h>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>

#define notVERBOSE

CadModel::CadModel(float length, float radius, const PaintCan& paint_can, float animation_id)
    : m_facet_count(0)
    , m_animation_id(NULL)
    , m_facet_v1(NULL)
    , m_facet_v2(NULL)
    , m_facet_v3(NULL)
    , m_facet_color(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(length=%8.6f, radius = %8.6f)\n", length, radius);
#endif
    m_facet_count = 4;
    m_animation_id = new float[m_facet_count];
    m_facet_v1 = new float3[m_facet_count];
    m_facet_v2 = new float3[m_facet_count];
    m_facet_v3 = new float3[m_facet_count];
    m_facet_color = new float3[m_facet_count];
    for (int i = 0; i < m_facet_count; i++) {
        m_animation_id[i] = animation_id;
        m_facet_color[i] = paint_can.ambient_color();
    }
    // end_face 1
    m_facet_v1[0] = {-radius, 0.0, 0.0};
    m_facet_v2[0] = {radius, 0.0, 0.0};
    m_facet_v3[0] = {0.0, 0.0, radius};
    // bottom_face
    m_facet_v1[1] = {radius, 0.0, 0.0};
    m_facet_v2[1] = {-radius, 0.0, 0.0};
    m_facet_v3[1] = {0.0, length, 0.0};
    // side_face 1
    m_facet_v1[2] = {radius, 0.0, 0.0};
    m_facet_v2[2] = {0.0, length, 0.0};
    m_facet_v3[2] = {0.0, 0.0, radius};
    // side_face 2
    m_facet_v1[3] = {0.0, length, 0.0};
    m_facet_v2[3] = {-radius, 0.0, 0.0};
    m_facet_v3[3] = {0.0, 0.0, radius};
}

CadModel::CadModel(const CadModel& cad_model, float x, float y, float z)
    : m_facet_count(0)
    , m_animation_id(NULL)
    , m_facet_v1(NULL)
    , m_facet_v2(NULL)
    , m_facet_v3(NULL)
    , m_facet_color(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(CadModel) offset = (%8.6f, %8.6f, %8.6f)\n", x, y, z);
#endif
    m_facet_count = cad_model.facets();
    if (m_facet_count > 0) {
        m_animation_id = new float[m_facet_count];
        m_facet_v1 = new float3[m_facet_count];
        m_facet_v2 = new float3[m_facet_count];
        m_facet_v3 = new float3[m_facet_count];
        m_facet_color = new float3[m_facet_count];
        float3 offset = {x, y, z};
        for (int i = 0; i < m_facet_count; i++) {
            m_animation_id[i] = cad_model.facet_animation_id(i);
            m_facet_v1[i] = translate(cad_model.facet_v1(i), offset);
            m_facet_v2[i] = translate(cad_model.facet_v2(i), offset);
            m_facet_v3[i] = translate(cad_model.facet_v3(i), offset);
            m_facet_color[i] = cad_model.facet_color(i);
        }
    }
}

CadModel::CadModel(const VrmlInterface& vrml_interface, float animation_id)
    : m_facet_count(0)
    , m_animation_id(NULL)
    , m_facet_v1(NULL)
    , m_facet_v2(NULL)
    , m_facet_v3(NULL)
    , m_facet_color(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(vrml) animation id = %7.3f)\n", animation_id);
#endif
    m_facet_count = vrml_interface.facets();
    if (m_facet_count > 0) {
        m_animation_id = new float[m_facet_count];
        m_facet_v1 = new float3[m_facet_count];
        m_facet_v2 = new float3[m_facet_count];
        m_facet_v3 = new float3[m_facet_count];
        m_facet_color = new float3[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            int3 v = vrml_interface.facet_points(i);
            int m = vrml_interface.facet_material(i);
            m_animation_id[i] = animation_id;
            m_facet_v1[i] = vrml_interface.point(v.v1);
            m_facet_v2[i] = vrml_interface.point(v.v2);
            m_facet_v3[i] = vrml_interface.point(v.v3);
            m_facet_color[i] = vrml_interface.ambient_color(m);
        }
    }
}

CadModel::CadModel(const StlInterface& stl_interface, const PaintCan& paint_can, float animation_id)
    : m_facet_count(0)
    , m_animation_id(NULL)
    , m_facet_v1(NULL)
    , m_facet_v2(NULL)
    , m_facet_v3(NULL)
    , m_facet_color(NULL)
{
#ifdef VERBOSE
    printf("CadModel::CadModel(stl), paint = (%8.6f, %8.6f, %8.6f) animation_id = %7.3f\n",
           paint_can.ambient_color().v1, paint_can.ambient_color().v2, paint_can.ambient_color().v3,
           animation_id);
#endif
    m_facet_count = stl_interface.facets();
    if (m_facet_count > 0) {
        m_animation_id = new float[m_facet_count];
        m_facet_v1 = new float3[m_facet_count];
        m_facet_v2 = new float3[m_facet_count];
        m_facet_v3 = new float3[m_facet_count];
        m_facet_color = new float3[m_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_animation_id[i] = animation_id;
            m_facet_v1[i] = stl_interface.facet_v1(i);
            m_facet_v2[i] = stl_interface.facet_v2(i);
            m_facet_v3[i] = stl_interface.facet_v3(i);
            m_facet_color[i] = paint_can.ambient_color();
        }
    }
}

CadModel::~CadModel()
{
#ifdef VERBOSE
    printf("~CadModel::CadModel()\n");
#endif
    if (m_animation_id != NULL)
        delete [] m_animation_id;
    if (m_facet_v1 != NULL)
        delete [] m_facet_v1;
    if (m_facet_v2 != NULL)
        delete [] m_facet_v2;
    if (m_facet_v3 != NULL)
        delete [] m_facet_v3;
    if (m_facet_color != NULL)
        delete [] m_facet_color;
}

void CadModel::add(const VrmlInterface& vrml_interface, float animation_id)
{
#ifdef VERBOSE
    printf("CadModel::add(vrml) animation_id = %7.3f\n", animation_id);
#endif
    int added_facet_count = vrml_interface.facets();
    if (added_facet_count > 0) {
        float* tva = m_animation_id;
        float3* tv1 = m_facet_v1;
        float3* tv2 = m_facet_v2;
        float3* tv3 = m_facet_v3;
        float3* tv4 = m_facet_color;
        m_animation_id = new float[m_facet_count + added_facet_count];
        m_facet_v1 = new float3[m_facet_count + added_facet_count];
        m_facet_v2 = new float3[m_facet_count + added_facet_count];
        m_facet_v3 = new float3[m_facet_count + added_facet_count];
        m_facet_color = new float3[m_facet_count + added_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_animation_id[i] = tva[i];
            m_facet_v1[i] = tv1[i];
            m_facet_v2[i] = tv2[i];
            m_facet_v3[i] = tv3[i];
            m_facet_color[i] = tv4[i];
        }
        for (int i = 0; i < added_facet_count; i++) {
            int3 v = vrml_interface.facet_points(i);
            int m = vrml_interface.facet_material(i);
            m_animation_id[m_facet_count + i] = animation_id;
            m_facet_v1[m_facet_count + i] = vrml_interface.point(v.v1);
            m_facet_v2[m_facet_count + i] = vrml_interface.point(v.v2);
            m_facet_v3[m_facet_count + i] = vrml_interface.point(v.v3);
            m_facet_color[m_facet_count + i] = vrml_interface.ambient_color(m);
        }
        m_facet_count += added_facet_count;
        delete [] tva;
        delete [] tv1;
        delete [] tv2;
        delete [] tv3;
        delete [] tv4;
    }
}

void CadModel::add(const StlInterface& stl_interface, const PaintCan& paint_can, float animation_id)
{
#ifdef VERBOSE
    printf("CadModel::add(stl) paint = (%8.6f, %8.6f, %8.6f) animation_id = %7.3f\n",
           paint_can.ambient_color().v1, paint_can.ambient_color().v2, paint_can.ambient_color().v3,
           animation_id);
#endif
    int added_facet_count = stl_interface.facets();
    if (added_facet_count > 0) {
        float* tva = m_animation_id;
        float3* tv1 = m_facet_v1;
        float3* tv2 = m_facet_v2;
        float3* tv3 = m_facet_v3;
        float3* tv4 = m_facet_color;
        m_animation_id = new float[m_facet_count + added_facet_count];
        m_facet_v1 = new float3[m_facet_count + added_facet_count];
        m_facet_v2 = new float3[m_facet_count + added_facet_count];
        m_facet_v3 = new float3[m_facet_count + added_facet_count];
        m_facet_color = new float3[m_facet_count + added_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_animation_id[i] = tva[i];
            m_facet_v1[i] = tv1[i];
            m_facet_v2[i] = tv2[i];
            m_facet_v3[i] = tv3[i];
            m_facet_color[i] = tv4[i];
        }
        for (int i = 0; i < added_facet_count; i++) {
            m_animation_id[m_facet_count + i] = animation_id;
            m_facet_v1[m_facet_count + i] = stl_interface.facet_v1(i);
            m_facet_v2[m_facet_count + i] = stl_interface.facet_v2(i);
            m_facet_v3[m_facet_count + i] = stl_interface.facet_v3(i);
            m_facet_color[m_facet_count +i] = paint_can.ambient_color();
        }
        m_facet_count += added_facet_count;
        delete [] tva;
        delete [] tv1;
        delete [] tv2;
        delete [] tv3;
        delete [] tv4;
    }
}

void CadModel::add(const CadModel& cad_model, float x, float y, float z)
{
#ifdef VERBOSE
    printf("CadModel::add(CadModel) offset = (%8.6f, %8.6f, %8.6f)\n", x, y, z);
#endif
    int added_facet_count = cad_model.facets();
    if (added_facet_count > 0) {
        float* tva = m_animation_id;
        float3* tv1 = m_facet_v1;
        float3* tv2 = m_facet_v2;
        float3* tv3 = m_facet_v3;
        float3* tv4 = m_facet_color;
        m_animation_id = new float[m_facet_count + added_facet_count];
        m_facet_v1 = new float3[m_facet_count + added_facet_count];
        m_facet_v2 = new float3[m_facet_count + added_facet_count];
        m_facet_v3 = new float3[m_facet_count + added_facet_count];
        m_facet_color = new float3[m_facet_count + added_facet_count];
        for (int i = 0; i < m_facet_count; i++) {
            m_animation_id[i] = tva[i];
            m_facet_v1[i] = tv1[i];
            m_facet_v2[i] = tv2[i];
            m_facet_v3[i] = tv3[i];
            m_facet_color[i] = tv4[i];
        }
        float3 offset = {x, y, z};
        for (int i = 0; i < added_facet_count; i++) {
            m_animation_id[m_facet_count + i] = cad_model.facet_animation_id(i);
            m_facet_v1[m_facet_count + i] = translate(cad_model.facet_v1(i), offset);
            m_facet_v2[m_facet_count + i] = translate(cad_model.facet_v2(i), offset);
            m_facet_v3[m_facet_count + i] = translate(cad_model.facet_v3(i), offset);
            m_facet_color[m_facet_count +i] = cad_model.facet_color(i);
        }
        m_facet_count += added_facet_count;
        delete [] tva;
        delete [] tv1;
        delete [] tv2;
        delete [] tv3;
        delete [] tv4;
    }
}

int CadModel::facets() const
{
    return m_facet_count;
}

float CadModel::facet_animation_id(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_animation_id[facet_ix];
    else
        return 0.0;
}

float3 CadModel::facet_v1(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v1[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_v2(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v2[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_v3(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_v3[facet_ix];
    else
        return {0.0, 0.0, 0.0};
}

float3 CadModel::facet_color(int facet_ix) const
{
    if (facet_ix < m_facet_count)
        return m_facet_color[facet_ix];
    else
        return float3{.0, 0.0, 0.0};
}

float3 CadModel::facet_normal(int facet_ix) const
{
    float3 p1, p2, p3;
    p1 = facet_v1(facet_ix);
    p2 = facet_v2(facet_ix);
    p3 = facet_v3(facet_ix);
    float3 va, vb;
    va.v1 = p2.v1 - p1.v1;
    va.v2 = p2.v2 - p1.v2;
    va.v3 = p2.v3 - p1.v3;
    vb.v1 = p3.v1 - p1.v1;
    vb.v2 = p3.v2 - p1.v2;
    vb.v3 = p3.v3 - p1.v3;
    float3 xp;
    xp.v1 = va.v2 * vb.v3 - vb.v2 * va.v3;
    xp.v2 = vb.v1 * va.v3 - va.v1 * vb.v3;
    xp.v3 = va.v1 * vb.v2 - vb.v1 * va.v2;
    return xp;
}

float3 CadModel::translate(const float3& v, const float3& offset) const
{
    float3 t;
    t.v1 = v.v1 + offset.v1;
    t.v2 = v.v2 + offset.v2;
    t.v3 = v.v3 + offset.v3;
    return t;
}

void CadModel::rotate_vertex(float3& vertex, const QMatrix4x4& matrix)
{
    QVector4D r = matrix * QVector4D(vertex.v1, vertex.v2, vertex.v3, 1.0);
    vertex.v1 = r.x();
    vertex.v2 = r.y();
    vertex.v3 = r.z();
}

void CadModel::rotate_ax(float angle)
{
    QVector3D my_axis = {1.0, 0.0, 0.0};
    QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, angle);
    QMatrix4x4 matrix;
    matrix.rotate(my_rot);
    for (int i = 0; i < m_facet_count; i++) {
        rotate_vertex(m_facet_v1[i], matrix);
        rotate_vertex(m_facet_v2[i], matrix);
        rotate_vertex(m_facet_v3[i], matrix);
    }
}

void CadModel::rotate_ay(float angle)
{
    QVector3D my_axis = {0.0, 1.0, 0.0};
    QQuaternion my_rot = QQuaternion::fromAxisAndAngle(my_axis, angle);
    QMatrix4x4 matrix;
    matrix.rotate(my_rot);
    for (int i = 0; i < m_facet_count; i++) {
        rotate_vertex(m_facet_v1[i], matrix);
        rotate_vertex(m_facet_v2[i], matrix);
        rotate_vertex(m_facet_v3[i], matrix);
    }
}

void CadModel::magnify(float factor)
{
    for (int i = 0; i < m_facet_count; i++) {
        m_facet_v1[i].v1 *= factor;
        m_facet_v1[i].v2 *= factor;
        m_facet_v1[i].v3 *= factor;
        m_facet_v2[i].v1 *= factor;
        m_facet_v2[i].v2 *= factor;
        m_facet_v2[i].v3 *= factor;
        m_facet_v3[i].v1 *= factor;
        m_facet_v3[i].v2 *= factor;
        m_facet_v3[i].v3 *= factor;
    }
}
