//
// stl_model.h
//
#if !defined(_STL_MODEL_H_)
#define _STL_MODEL_H_

#include "cad_model.h"
#include <QString>
#include "stl_interface.h"
#include "float3.h"
#include "int3.h"
#include "paint_can.h"

class StlModel: public CadModel
{
public:
    StlModel(const PaintCan& paint_can, const QString& file_name);
    ~StlModel();
    int facets() const override;
    float3 facet_v1(int facet_ix) const override;
    float3 facet_v2(int facet_ix) const override;
    float3 facet_v3(int facet_ix) const override;
    float3 facet_color(int facet_ix) const override;

protected:
    PaintCan m_paint_can;
    StlInterface m_si;

private:
};

#endif // _STL_MODEL_H_
