
#ifndef _THINGUS_H_
#define _THINGUS_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Thingus : protected QOpenGLFunctions
{
public:
    Thingus();
    virtual ~Thingus();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // _THINGUS_H_
