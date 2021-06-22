
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"

#define BAT_PIVOT_X -0.88235
#define BAT_PIVOT_Z 1.0
#define TARGET_PIVOT_Y -1.0
#define TARGET_PIVOT_Z -7.8

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus();
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    CadModel *m_cad = nullptr;

    void initCubeGeometry();
    int m_vertices;
    QOpenGLBuffer vertexBuf;
};

#endif // _THINGUS_H_
