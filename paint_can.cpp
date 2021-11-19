
#include "paint_can.h"

PaintCan::PaintCan(float r, float g, float b, float diffuse, float specular, float shiny)
    : m_ambient({r, g, b})
    , m_diffuse({r * diffuse, g * diffuse, b * diffuse})
    , m_specular({r * specular, g * specular, b * specular})
    , m_emissive({0.0, 0.0, 0.0})
    , m_shininess(shiny)
    , m_transparency(0.0)
{
}

PaintCan::~PaintCan()
{
}

Float3 PaintCan::ambient_color() const
{
    return m_ambient;
}

Float3 PaintCan::diffuse_color() const
{
    return m_diffuse;
}

Float3 PaintCan::specular_color() const
{
    return m_specular;
}

Float3 PaintCan::emissive_color() const
{
    return m_emissive;
}

float PaintCan::shininess() const
{
    return m_shininess;
}

float PaintCan::transparency() const
{
    return m_transparency;
}

