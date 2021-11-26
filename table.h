
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "document.h"
#include "view.h"
#include "history.h"
#include <QOpenGLWidget>
#include <QMouseEvent>

class Table: public QOpenGLWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent = nullptr);
    ~Table();
    void undo();
    void redo();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    View* m_view;
    History m_history;
};

#endif // _TABLE_H_
