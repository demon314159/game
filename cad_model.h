//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>
#include "float3.h"
#include "int3.h"

class CadModel
{
public:
    CadModel();
    virtual ~CadModel();
    virtual int facets() const = 0;
    virtual float3 facet_v1(int facet_ix) const = 0;
    virtual float3 facet_v2(int facet_ix) const = 0;
    virtual float3 facet_v3(int facet_ix) const = 0;
    virtual float3 facet_color(int facet_ix) const = 0;
    float3 facet_normal(int facet_ix) const;

private:
};

#endif // _CAD_MODEL_H_
