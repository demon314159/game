//
// cad_model.h
//
#if !defined(_CAD_MODEL_H_)
#define _CAD_MODEL_H_

#include <QString>
#include "vrml_interface.h"
#include "float3.h"
#include "int3.h"

class CadModel
{
public:
    CadModel(const QString& file_name);
    ~CadModel();
    int facets() const;
    float3 facet_v1(int facet_ix) const;
    float3 facet_v2(int facet_ix) const;
    float3 facet_v3(int facet_ix) const;
    float3 facet_color(int facet_ix) const;

// temporary approach for continuity
    int vertices() const;
    void get_vertex(int ix, float& x, float& y, float& z) const;
    void get_facet(int ix, int& a, int& b, int& c) const;
#ifdef NEVERMORE
    int image_size() const;
    float* image_data() const;
#endif

protected:
    VrmlInterface m_vi;

private:
};

#endif // _CAD_MODEL_H_
