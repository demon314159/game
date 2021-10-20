
#include "elements.h"
#include <stdio.h>

Element::Element(float3 dim, float3 pos)
    : m_dim(dim)
    , m_pos(pos)
{
    printf("Element()\n");
}

Element::~Element()
{
    printf("~Element()\n");
}


BrickElement::BrickElement(float3 dim, float3 pos, float dimb)
    : Element(dim, pos)
    , m_dimb(dimb)
{
    printf("BrickElement()\n");
}

BrickElement::~BrickElement()
{
    printf("~BrickElement()\n");
}



