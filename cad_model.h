//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>
#include <QMatrix4x4>
#include "float3.h"
#include "int3.h"
#include "vrml_interface.h"
#include "stl_interface.h"
#include "paint_can.h"

class CadModel
{
public:
    CadModel(float length, float radius, const PaintCan& paint_can, float animation_id = 0.0);
    CadModel(const CadModel& cad_model, float x = 0.0, float y = 0.0, float z = 0.0);
    CadModel(const VrmlInterface& vrml_interface, float animation_id = 0.0);
    CadModel(const StlInterface& stl_interface, const PaintCan& paint_can, float animation_id = 0.0);
    ~CadModel();
    void add(const VrmlInterface& vrml_interface, float animation_id = 0.0);
    void add(const StlInterface& stl_interface, const PaintCan& paint_can, float animation_id = 0.0);
    void add(const CadModel& cad_model, float x = 0.0, float y = 0.0, float z = 0.0);
    void rotate_ax(float angle);
    void rotate_ay(float angle);
    void magnify(float factor);
    int facets() const;
    float facet_animation_id(int facet_ix) const;
    float3 facet_v1(int facet_ix) const;
    float3 facet_v2(int facet_ix) const;
    float3 facet_v3(int facet_ix) const;
    float3 facet_color(int facet_ix) const;
    float3 facet_normal(int facet_ix) const;
    float3 translate(const float3& v, const float3& offset) const;

protected:
    void rotate_vertex(float3& vertex, const QMatrix4x4& matrix);

private:
    int m_facet_count;
    float* m_animation_id;
    float3* m_facet_v1;
    float3* m_facet_v2;
    float3* m_facet_v3;
    float3* m_facet_color;
};

#endif // _CAD_MODEL_H_
