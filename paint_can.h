
#ifndef _PAINT_CAN_H_
#define _PAINT_CAN_H_

#include "float3.h"

class PaintCan
{
public:
    PaintCan(float r, float g, float b, float diffuse = 1.0, float specular = 0.5, float shiny = 0.5);
    ~PaintCan();

    float3 ambient_color() const;
    float3 diffuse_color() const;
    float3 specular_color() const;
    float3 emissive_color() const;
    float shininess() const;
    float transparency() const;

private:
    float3 m_ambient;
    float3 m_diffuse;
    float3 m_specular;
    float3 m_emissive;
    float m_shininess;
    float m_transparency;
};

#endif // _PAINT_CAN_H_
