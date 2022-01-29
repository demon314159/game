
// table.h
//
#if !defined(_TABLE_H_)
#define _TABLE_H_

#include "document.h"
#include "view.h"
#include "history.h"
#include "morph_element.h"
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

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void spawn_add_element_command();
    void spawn_delete_element_command(int ix);
    Float3 corrected_pos(Float3 pos, float dx, float dy, float dz, int orientation) const;
    void set_morph_button(Float3 pos, int orientation);
    void clear_morph_button();
private:
    View* m_view;
    History m_history;
    MorphElement m_me;
};

#endif // _TABLE_H_
