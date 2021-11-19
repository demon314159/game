
#ifndef _PAINT_CAN_H_
#define _PAINT_CAN_H_

#include "float3.h"

class PaintCan
{
public:
    PaintCan(float r, float g, float b, float diffuse = 1.0, float specular = 0.5, float shiny = 0.5);
    ~PaintCan();

    Float3 ambient_color() const;
    Float3 diffuse_color() const;
    Float3 specular_color() const;
    Float3 emissive_color() const;
    float shininess() const;
    float transparency() const;

private:
    Float3 m_ambient;
    Float3 m_diffuse;
    Float3 m_specular;
    Float3 m_emissive;
    float m_shininess;
    float m_transparency;
};

#endif // _PAINT_CAN_H_
