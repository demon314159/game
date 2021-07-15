
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"

#define ANI_ID_TARGET1 1.0
#define ANI_ID_TARGET2 2.0
#define ANI_ID_TARGET3 3.0
#define ANI_ID_TARGET4 4.0
#define ANI_ID_TARGET5 5.0
#define ANI_ID_TARGET6 6.0
#define ANI_ID_TARGET7 7.0
#define ANI_ID_BAT     8.0
#define ANI_ID_PITCH   9.0

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
