//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>
#include "float3.h"
#include "int3.h"
#include "vrml_interface.h"
#include "stl_interface.h"
#include "paint_can.h"

class CadModel
{
public:
    CadModel(const VrmlInterface& vrml_interface);
    CadModel(const StlInterface& stl_interface, const PaintCan& paint_can);
    ~CadModel();
    int facets() const;
    float3 facet_v1(int facet_ix) const;
    float3 facet_v2(int facet_ix) const;
    float3 facet_v3(int facet_ix) const;
    float3 facet_color(int facet_ix) const;
    float3 facet_normal(int facet_ix) const;

private:
    int m_facet_count;
    float3* m_facet_v1;
    float3* m_facet_v2;
    float3* m_facet_v3;
    float3* m_facet_color;
};

#endif // _CAD_MODEL_H_
