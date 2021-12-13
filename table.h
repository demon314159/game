
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
    void add_ledge_element();
    void add_window_element();
    void add_no_element();
    void edit_element_bigger();
    void edit_element_smaller();
    void edit_element_cancel();
    void edit_element_done();

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
    void handle_large_element();
private:
    View* m_view;
    History m_history;
    Float3 m_le_pos;
    int m_le_span;
    int m_le_height;
    int m_le_orientation;
    QPoint m_le_global_pos;
    Command* m_le_command;
};

#endif // _TABLE_H_
