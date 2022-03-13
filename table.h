
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "document.h"
#include "view.h"
#include "history.h"
#include "morph_element.h"
#include "navigate.h"
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>

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
    void spawn_add_element_command();
    void spawn_delete_element_command(int ix);
    Float3 corrected_pos(Float3 pos, float dx, float dy, float dz, int orientation) const;
    void do_command(Command* c);
    void set_history_buttons();
    void add_morph_button();
    void update_morph_element();
    void cancel_morph();
private:
    View* m_view;
    History m_history;
    MorphElement m_me;
    Navigate m_navigate;
};

#endif // _TABLE_H_
