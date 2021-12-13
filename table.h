
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
    void undo_command();
    void redo_command();
    void new_command();
    void load_command();
    void save_command();

public slots:
    void handle_ledge();
    void handle_window();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void spawn_add_element_command(QMouseEvent* e);
    void spawn_delete_element_command(int ix);
    void handle_large_element(QMouseEvent* e);
private:
    View* m_view;
    History m_history;
    Float3 m_le_pos;
    int m_le_span;
    int m_le_orientation;
};

#endif // _TABLE_H_
