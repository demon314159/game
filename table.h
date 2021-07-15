
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
    Table(int& view_index, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, ImageSet& image_set, QStackedWidget* stacked_widget, QWidget *parent = nullptr);
    ~Table();
    QImage the_image();

protected:
    void timerEvent(QTimerEvent *e) override;
    bool grab_image(int slot, QImage& image);
    bool grab_ani_image(int slot, AnimatedImage& ai);
    bool grab_digit_set(int index, int& adigit, AnimatedImage (&digit)[ImageSet::DIGITS]);
    void digit_difference(AnimatedImage (& digit)[ImageSet::DIGITS]);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
private:
    ImageSet& m_image_set;
    QStackedWidget* m_stacked_widget;
    int m_timer_step;
    QImage m_image;
    float m_tilt;
    float m_target_ani_id;
    float m_bat_angle;
    float m_ani_angle2;
    float m_ani_angle3;
    bool m_ball_in_play;
    bool m_ball_hit;
    int m_outs;
    int m_left_digit;
    int m_middle_digit;
    int m_right_digit;
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
    int& m_view_ix;
    QMatrix4x4& m_mvp_matrix;
    QMatrix4x4& m_rot_matrix;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // _TABLE_H_
