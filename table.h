
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "view.h"
#include "navigate.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QBasicTimer>

class Table: public QOpenGLWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void mouse_navigate(QMouseEvent* e);
    void timerEvent(QTimerEvent *e) override;
private:
    View* m_view;
    Navigate m_navigate;
    QBasicTimer m_timer;
};

#endif // _TABLE_H_
