
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "thingus.h"
#include "float3.h"
#include "document.h"
#include "view.h"
#include "history.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
#ifdef NEVERMORE
    QPoint w2s(const QVector3D point) const;
    void select_brick(int x, int y);
    bool inside_face(const Face& f, int sx, int sy);
    int zcross(const QPoint& a, const QPoint& b, int sx, int sy) const;
    float distance(float3 pos1, float3 pos2) const;
#endif
private:
    Document m_doc;
    View m_view;
    History m_history;

    int m_ms_at_start;
    float m_xrot;
    float m_yrot;
    qreal m_aspect;
    float m_fov;
    float m_camz;
    bool m_marker_flag;
    float3 m_marker_pos;

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
    QQuaternion rotation;
};

#endif // _TABLE_H_
