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

// temporary approach for continuity
    int vertices() const;
    int facets() const;
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
