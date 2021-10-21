
#include "elements.h"
#include <stdio.h>

Element::Element(float3 pos)
    : m_pos(pos)
{
}

HalfBrickElement::HalfBrickElement(float xpos, float ypos, float zpos)
    : Element({xpos, ypos, zpos})
{
}

BrickElement::BrickElement(float xpos, float ypos, float zpos, int orientation)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
{
}

WindowElement::WindowElement(float xpos, float ypos, float zpos, int orientation,
                             float width, float height, int hgrilles, int vgrilles)
    : Element({xpos, ypos, zpos})
    , m_orientation(orientation)
    , m_width(width)
    , m_height(height)
    , m_hgrilles(hgrilles)
    , m_vgrilles(vgrilles)
{
}




