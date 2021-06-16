
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "cad_model.h"

#include "bin_interface.h"

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus();
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    CadModel *m_cad = nullptr;

    BinInterface *m_bin = nullptr;

    void initCubeGeometry();
    int m_vertices;
    QOpenGLBuffer vertexBuf;
};

#endif // _THINGUS_H_
