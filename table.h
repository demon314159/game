
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "thingus.h"
#include "float3.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>

class Table: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Table(int& view_index, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, QWidget *parent = nullptr);
    ~Table();

protected:
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void resize_calc();
private:
    int m_ms_at_start;
    float m_xrot;
    float m_yrot;
    qreal m_aspect;
    float m_camz;

    int m_width;
    int m_height;
    QBasicTimer timer;
    QOpenGLShaderProgram m_program;
    Thingus* m_thingy;
    QMatrix4x4 m_projection;
    int& m_view_ix;
    QMatrix4x4& m_mvp_matrix;
    QMatrix4x4& m_rot_matrix;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // _TABLE_H_
