
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"
#include "float3.h"
#include "document.h"

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus(Document& doc);
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    float radius() const;
    float3 center() const;

private:
    CadModel *m_cad = nullptr;
    void initCubeGeometry();
    int m_vertices;
    float m_radius;
    float3 m_center;
    QOpenGLBuffer vertexBuf;
};

#endif // _THINGUS_H_
