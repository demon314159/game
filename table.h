
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "document.h"
#include "view.h"
#include "history.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QAction>

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
    void edit_element_bigger();
    void edit_element_smaller();
    void edit_element_more_v();
    void edit_element_less_v();
    void edit_element_more_h();
    void edit_element_less_h();
    void edit_element_flip();
    void edit_element_cancel();
    void edit_element_done();

protected:
    void set_up_actions();
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
    void add_window_element();
    void add_door_element();
    void add_generic_element();
private:
    View* m_view;
    History m_history;
    Float3 m_le_pos;
    int m_le_span;
    int m_le_height;
    int m_le_orientation;
    bool m_le_gap;
    int m_le_v;
    int m_le_h;
    bool m_le_door;
    QPoint m_le_global_pos;
    Command* m_le_command;
    QAction* m_window_action;
    QAction* m_door_action;
    QAction* m_no_action;
    QAction* m_bigger_action;
    QAction* m_smaller_action;
    QAction* m_more_v_action;
    QAction* m_less_v_action;
    QAction* m_more_h_action;
    QAction* m_less_h_action;
    QAction* m_flip_action;
    QAction* m_cancel_action;
    QAction* m_done_action;
};

#endif // _TABLE_H_
