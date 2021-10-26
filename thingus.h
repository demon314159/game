
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"
#include "float3.h"

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus();
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    float rad_xz() const;
    float3 center() const;

private:
    CadModel *m_cad = nullptr;
    void initCubeGeometry();
    int m_vertices;
    float m_rad_xz;
    float3 m_center;
    QOpenGLBuffer vertexBuf;
};

#endif // _THINGUS_H_
