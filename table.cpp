//
// table.cpp
//
#include "table.h"
#include <QMouseEvent>
#include <QFileDialog>
#include <QMenu>
#include <QtGui>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view(new View(new Document(QString("house.brk"))))
    , m_le_pos({0.0, 0.0, 0.0})
    , m_le_span(0)
    , m_le_height(0)
    , m_le_orientation(0)
    , m_le_gap(false)
    , m_le_v(0)
    , m_le_h(0)
    , m_le_door(false)
    , m_le_command(NULL)
    , m_window_action(NULL)
    , m_door_action(NULL)
    , m_no_action(NULL)
    , m_bigger_action(NULL)
    , m_smaller_action(NULL)
    , m_more_v_action(NULL)
    , m_less_v_action(NULL)
    , m_more_h_action(NULL)
    , m_less_h_action(NULL)
    , m_flip_action(NULL)
    , m_cancel_action(NULL)
    , m_done_action(NULL)
{
    setMinimumWidth(600);
    setMinimumHeight(337);
//    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
    set_up_actions();
}

Table::~Table()
{
    makeCurrent();
    delete m_view;
    doneCurrent();
}

void Table::set_up_actions()
{
    m_bigger_action = new QAction("Taller", this);
    connect(m_bigger_action, SIGNAL(triggered()), this, SLOT(edit_element_bigger()));
    m_smaller_action = new QAction("Shorter", this);
    connect(m_smaller_action, SIGNAL(triggered()), this, SLOT(edit_element_smaller()));
    m_more_v_action = new QAction("Add vertical grille", this);
    connect(m_more_v_action, SIGNAL(triggered()), this, SLOT(edit_element_more_v()));
    m_less_v_action = new QAction("Remove vertical grille", this);
    connect(m_less_v_action, SIGNAL(triggered()), this, SLOT(edit_element_less_v()));
    m_more_h_action = new QAction("Add horizontal grille", this);
    connect(m_more_h_action, SIGNAL(triggered()), this, SLOT(edit_element_more_h()));
    m_less_h_action = new QAction("Remove horizontal grille", this);
    connect(m_less_h_action, SIGNAL(triggered()), this, SLOT(edit_element_less_h()));
    m_flip_action = new QAction("Flip", this);
    connect(m_flip_action, SIGNAL(triggered()), this, SLOT(edit_element_flip()));
    m_cancel_action = new QAction("Cancel", this);
    connect(m_cancel_action, SIGNAL(triggered()), this, SLOT(edit_element_cancel()));
    m_done_action = new QAction("Done", this);
    connect(m_done_action, SIGNAL(triggered()), this, SLOT(edit_element_done()));
}

void Table::initializeGL()
{
    if (!m_view->initialize())
        close();
}

void Table::resizeGL(int w, int h)
{
    m_view->resize(w, h);
}

void Table::paintGL()
{
    m_view->paint();
}

void Table::keyPressEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    bool shifted = (e->modifiers() & Qt::ShiftModifier) ? true : false;
    if (a == 0x6f) { // up
        m_view->rotate_ax(-(shifted ? 1.0 : 10.0));
        update();
    } else if (a == 0x74) { // down
        m_view->rotate_ax(shifted ? 1.0 : 10.0);
        update();
    } else if (a == 0x71) { // left
        m_view->rotate_ay(-(shifted ? 1.0 : 10.0));
        update();
    } else if (a == 0x72) { // right
        m_view->rotate_ay(shifted ? 1.0 : 10.0);
        update();
    } else if (a == 0x1f) { // i or I
        m_view->zoom(shifted ? (29.0 / 30.0) : (2.0 / 3.0));
        update();
    } else if (a == 0x20) { // o or O
        m_view->zoom(shifted ? (30.0 / 29.0) : (3.0 / 2.0));
        update();
    } else if (a == 0x2b) { // h or H
        m_view->zoom_home();
        if (shifted)
            m_view->rotate_home();
        update();
    } else if (a == 0x1e) { // u or U
        undo_command();
    } else if (a == 0x1b) { // r or R
        redo_command();
    } else if (a == 0x36) { // c or C
        if (shifted) {
            int n = m_view->get_doc()->elements();
            if (n > 0) {
                m_history.do_command(new RemoveElementCommand(n - 1, m_view));
            } else {
                printf("no more elements\n");
            }
        }
        else
          m_history.do_command(new AddElementCommand(new BrickElement(0.0, 10.0, 0.0, 0), m_view));
        update();
    } else if (a == 0x39) { // n or N
        new_command();
    } else if (a == 0x2e) { // l or L
        load_command();
    } else if (a == 0x27) { // s or S
        save_command();
    } else if (a == 0x09) {
        m_view->mouse_unselect();
        update();
    } else {
        printf("unknown key %02x\n", a);
    }
    QOpenGLWidget::keyPressEvent(e);
}

void Table::keyReleaseEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    if (a == 0x32) {
    } else if (a == 0x3e) {
    }
    QOpenGLWidget::keyReleaseEvent(e);
}

void Table::add_window_element()
{
    m_le_door = false;
    add_generic_element();
}

void Table::add_door_element()
{
    m_le_door = true;
    add_generic_element();
}

void Table::add_generic_element()
{
    if (m_le_door)
        m_le_command = new AddElementCommand(new DoorElement(m_le_pos.v1, m_le_pos.v2 + m_le_height / 2.0, m_le_pos.v3, m_le_orientation, m_le_span + 1, m_le_height, m_le_h, m_le_v), m_view);
    else
        m_le_command = new AddElementCommand(new WindowElement(m_le_pos.v1, m_le_pos.v2 + m_le_height / 2.0, m_le_pos.v3, m_le_orientation, m_le_span + 1, m_le_height, m_le_h, m_le_v), m_view);
    m_history.do_command(m_le_command);
    update();

    QMenu menu(this);

    menu.addAction(m_bigger_action);
    if (m_le_height > 3.0)
        menu.addAction(m_smaller_action);
    menu.addAction(m_more_v_action);
    if (m_le_v > 0)
        menu.addAction(m_less_v_action);
    menu.addAction(m_more_h_action);
    if (m_le_h > 0)
        menu.addAction(m_less_h_action);
    menu.addAction(m_flip_action);
    menu.addAction(m_cancel_action);
    menu.addAction(m_done_action);
    menu.exec(m_le_global_pos);
}

void Table::edit_element_bigger()
{
    m_history.undo_command();
    ++m_le_height;
    add_generic_element();
}

void Table::edit_element_smaller()
{
    m_history.undo_command();
    if (m_le_height > 3.0) {
        --m_le_height;
    }
    add_generic_element();
}

void Table::edit_element_more_v()
{
    m_history.undo_command();
    ++m_le_v;
    add_generic_element();
}

void Table::edit_element_less_v()
{
    m_history.undo_command();
    if (m_le_v > 0) {
        --m_le_v;
    }
    add_generic_element();
}

void Table::edit_element_more_h()
{
    m_history.undo_command();
    ++m_le_h;
    add_generic_element();
}

void Table::edit_element_less_h()
{
    m_history.undo_command();
    if (m_le_h > 0) {
        --m_le_h;
    }
    add_generic_element();
}

void Table::edit_element_flip()
{
    m_history.undo_command();
    m_le_orientation = (m_le_orientation + 2) & 3;
    add_generic_element();
}

void Table::edit_element_cancel()
{
    m_history.undo_command();
    update();
}

void Table::edit_element_done()
{
}

void Table::handle_large_element()
{
    if (m_le_pos.v2 < 1.0) {
        m_le_height = (float) round((m_le_span + 1.0) * (4.0 / 2.0) * (3.0 / 2.0)); // 4/2 * 3/2
        add_door_element();
    } else if (!m_le_gap)
        add_window_element();
    else
        m_view->mouse_unselect();
}

void Table::spawn_add_element_command(QMouseEvent* e)
{
    Float3 pos;
    int span;
    int orientation;
    bool same_level;
    bool roof;
    if (m_view->new_element_chosen(pos, span, orientation, same_level, roof)) {
        if (span == 0) {
            if (same_level) {
                if (roof)
                    m_history.do_command(new AddElementCommand(new RoofElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation, span + 1), m_view));
                else
                    m_history.do_command(new AddElementCommand(new HalfBrickElement(pos.v1, pos.v2 + 0.5, pos.v3), m_view));
            }
        } else if (span == 1) {
            if (same_level)
                    m_history.do_command(new AddElementCommand(new BrickElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation), m_view));
                else
                    m_history.do_command(new AddElementCommand(new GableBrickElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation), m_view));
        } else {
            if (same_level) {
                if (roof) {
                    m_history.do_command(new AddElementCommand(new RoofElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation, span + 1), m_view));
                } else {
                    if (m_view->span_blocked()) {
                        m_view->mouse_unselect();
                        update();
                    } else {
                        update();
                        m_le_pos = pos;
                        m_le_span = span;
                        m_le_height = (float) round((m_le_span + 1.0) * 2.0); // 4/3 * 3/2
                        m_le_orientation = orientation;
                        m_le_gap = m_view->gap_below_span();
                        m_le_v = 1;
                        m_le_h = 2;
                        m_le_global_pos = e->globalPos();
                        handle_large_element();
                    }
                }
            }
        }
    }
}

void Table::spawn_delete_element_command(int ix)
{
    if (ix >= 0) {
        m_history.do_command(new RemoveElementCommand(ix, m_view));
    }
}

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_view->mouse_select(e->pos().x(), e->pos().y());
        spawn_add_element_command(e);
        update();
    } else if (e->button() == Qt::RightButton) {
        int ix = m_view->mouse_delete(e->pos().x(), e->pos().y());
        spawn_delete_element_command(ix);
        update();
    }
    QOpenGLWidget::mousePressEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
    } else if (e->button() == Qt::RightButton) {
    }
    QOpenGLWidget::mouseReleaseEvent(e);
}

void Table::undo_command()
{
    if (!m_history.end_of_undo()) {
        m_history.undo_command();
        update();
    } else {
//        printf("At first command\n");
    }
}

void Table::redo_command()
{
    if (!m_history.end_of_redo()) {
        m_history.redo_command();
        update();
    } else {
//        printf("At last command\n");
    }
}

void Table::new_command()
{
    m_history.do_command(new NewCommand(m_view));
    update();
}

void Table::load_command()
{
    releaseKeyboard();
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open Brick File"), "", tr("BRK Files (*.brk)"));
    grabKeyboard();
    if (file_name.length() == 0) {
        printf("No file selected\n");
        return;
    }
    m_history.do_command(new LoadCommand(file_name, m_view));
    update();
}

void Table::save_command()
{
    releaseKeyboard();
    QString file_name = QFileDialog::getSaveFileName(this,
        tr("Open Brick File"), "", tr("BRK Files (*.brk)"));
    grabKeyboard();
    if (file_name.length() == 0) {
        printf("No file selected\n");
        return;
    }
    Document* doc = m_view->get_doc();
    QString error_msg;
    if (!doc->save(file_name, error_msg)) {
        printf("<<< error saving file '%s': %s >>>\n", file_name.toLatin1().data(), error_msg.toLatin1().data());
    }
}

