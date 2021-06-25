
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "thingus.h"
#include "float3.h"
#include "image_set.h"

#include <QStackedWidget>
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
    Table(ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent = nullptr);
    ~Table();
    QImage the_image();

protected:
    float3 ball_position_now();
#ifdef NEVERMORE
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
#endif
    void timerEvent(QTimerEvent *e) override;
    bool grab_image(int slot, QImage& image);
    bool grab_ani_image(int slot, AnimatedImage& ai, const QImage& baseline);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
private:
    ImageSet& m_image_set;
    QStackedWidget* m_stacked_widget;
    int m_timer_step;
    QImage m_image;
    float m_ani_sel2;
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
    QBasicTimer timer;
    QOpenGLShaderProgram m_program;
    Thingus* m_thingy;
    QMatrix4x4 m_projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // _TABLE_H_
