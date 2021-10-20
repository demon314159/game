
#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

#include "float3.h"

class Element
{
public:
    Element(float3 dim, float3 pos);
    Element() = delete;
    virtual ~Element();

private:
    float3 m_dim;
    float3 m_pos;
};

class BrickElement: public Element
{
public:
    BrickElement(float3 dim, float3 pos, float dimb);
    BrickElement() = delete;
    virtual ~BrickElement();

private:
    float m_dimb;
};

#endif // _ELEMENTS_H_
