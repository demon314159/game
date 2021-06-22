
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "thingus.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Table: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

protected:

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
    void initTextures();
private:
    int m_ani_angle1;
    int m_ani_angle2;
    int m_ani_angle3;
    int m_width;
    int m_height;
    unsigned int m_frame_count;
    QBasicTimer timer;
    QOpenGLShaderProgram m_program;
    Thingus* m_thingy;
    QOpenGLTexture* m_texture;
    QMatrix4x4 m_projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // _TABLE_H_
