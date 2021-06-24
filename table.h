
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
#include <QOpenGLTexture>

class Table: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();
    QImage the_image();

protected:
    float3 ball_position_now();
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
    void initTextures();
private:
    int m_timer_step;
    QImage m_image;
    float m_ani_angle1;
    float m_ani_angle2;
    float m_ani_angle3;
    bool m_ball_in_play;
    bool m_ball_hit;
    bool m_blocker;
    int m_t0;
    int m_th;
    float3 m_ball_pos0;
    float3 m_hit_pos;

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
