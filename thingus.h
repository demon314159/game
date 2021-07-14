
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"

#define BAT_PIVOT_X -0.88235
#define BAT_PIVOT_Z 1.0
#define TARGET_WIDTH 0.416
#define TARGET_PIVOT_Y 0.025
#define TARGET_PIVOT_Z (-7.4 -0.025)

#define PITCH_PIVOT_Z -4.0

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus(float tilt);
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    float m_tilt;
    CadModel *m_cad = nullptr;

    void initCubeGeometry();
    int m_vertices;
    QOpenGLBuffer vertexBuf;
};

#endif // _THINGUS_H_
