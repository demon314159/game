
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "float3.h"

class Material
{
public:
    Material(float3 dim, float3 pos);
    ~Material();

private:
    float3 m_dim;
    float3 m_pos;
};

#endif // _MATERIAL_H_
