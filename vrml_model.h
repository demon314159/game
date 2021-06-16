//
// vrml_model.h
//
#if !defined(_VRML_MODEL_H_)
#define _VRML_MODEL_H_

#include "cad_model.h"
#include <QString>
#include "vrml_interface.h"
#include "float3.h"
#include "int3.h"

class VrmlModel: public CadModel
{
public:
    VrmlModel(const QString& file_name);
    ~VrmlModel();
    int facets() const override;
    float3 facet_v1(int facet_ix) const override;
    float3 facet_v2(int facet_ix) const override;
    float3 facet_v3(int facet_ix) const override;
    float3 facet_color(int facet_ix) const override;

protected:
    VrmlInterface m_vi;

private:
};

#endif // _VRML_MODEL_H_
