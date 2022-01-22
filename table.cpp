//
// table.cpp
//
#include "table.h"
#include "look.h"
#include <QMouseEvent>
#include <QFileDialog>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view(new View(new Document(QString("house.brk"))))
    , m_le_command(NULL)
{
    setMinimumWidth(600);
    setMinimumHeight(337);
//    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
}

Table::~Table()
{
    makeCurrent();
    delete m_view;
    doneCurrent();
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
        if (!m_view->get_vmenu().menu_active()) {
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
        }
    } else if (a == 0x39) { // n or N
        new_command();
    } else if (a == 0x2e) { // l or L
        load_command();
    } else if (a == 0x27) { // s or S
        save_command();
    } else if (a == 0x09) {
        m_view->mouse_unselect();
        m_view->get_vmenu().clear();
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

Float3 Table::corrected_pos(Float3 pos, float dx, float dy, float dz, int orientation) const
{
    Float3 p = pos;
    if (orientation == 0) {
        p.v1 += dx;
        p.v3 += dz;
    } else if (orientation == 1) {
        p.v1 += dz;
        p.v3 -= dx;
    } else if (orientation == 2) {
        p.v1 -= dx;
        p.v3 -= dz;
    } else if (orientation == 3) {
        p.v1 -= dz;
        p.v3 += dx;
    }
    p.v2 = Look::dimh * p.v2 + (Look::dimh * m_le.height() + Look::dimh * dy);
    return p;
}

void Table::add_generic_element()
{
    if (m_le.is_gap_below() && m_le.pos().v2 > 0.5) {
        m_le_command = new AddElementCommand(new LedgeElement(m_le.pos().v1, m_le.pos().v2 + 0.5, m_le.pos().v3, m_le.orientation(), m_le.span() + 1), m_view);
        m_history.do_command(m_le_command);
        update();
        return;
    } else if (m_le.is_door()) {
        m_le_command = new AddElementCommand(new DoorElement(m_le.pos().v1, m_le.pos().v2 + m_le.height() / 2.0, m_le.pos().v3, m_le.orientation(), m_le.span() + 1, m_le.height(), m_le.hgrilles(), m_le.vgrilles()), m_view);
    } else {
        m_le_command = new AddElementCommand(new WindowElement(m_le.pos().v1, m_le.pos().v2 + m_le.height() / 2.0, m_le.pos().v3, m_le.orientation(), m_le.span() + 1, m_le.height(), m_le.hgrilles(), m_le.vgrilles()), m_view);
    }
    m_history.do_command(m_le_command);
    update();

    Vmenu& vmenu = m_view->get_vmenu();
    vmenu.clear();

    float dx = Look::dimx / 2;
    vmenu.add_increase_height(corrected_pos(m_le.pos(), -dx, 0.5, 0.6, m_le.orientation()), m_le.orientation());
    vmenu.add_decrease_height(corrected_pos(m_le.pos(), dx, 0.5, 0.6, m_le.orientation()), m_le.orientation());
    vmenu.add_done(corrected_pos(m_le.pos(), dx + Look::dimx, 0.5, 0.6, m_le.orientation()), m_le.orientation());
    vmenu.add_cancel(corrected_pos(m_le.pos(), - dx - Look::dimx, 0.5, 0.6, m_le.orientation()), m_le.orientation());
    vmenu.add_increase_vgrilles(corrected_pos(m_le.pos(), + 3 * dx / 4, -0.375, 0.45, m_le.orientation()), m_le.orientation());
    vmenu.add_decrease_vgrilles(corrected_pos(m_le.pos(), - 3 * dx / 4, -0.375, 0.45, m_le.orientation()), m_le.orientation());
    if (m_le.is_door()) {
        vmenu.add_increase_hgrilles(corrected_pos(m_le.pos(), 0.25 - 0.5 * (m_le.span() + 1), -0.18 * m_le.height() + 0.5, 0.45, m_le.orientation()), m_le.orientation());
        vmenu.add_decrease_hgrilles(corrected_pos(m_le.pos(), 0.25 - 0.5 * (m_le.span() + 1), -0.18 * m_le.height() - 0.5, 0.45, m_le.orientation()), m_le.orientation());
    } else {
        vmenu.add_increase_hgrilles(corrected_pos(m_le.pos(), 0.25 - 0.5 * (m_le.span() + 1), -m_le.height() / 2 + 0.5, 0.45, m_le.orientation()), m_le.orientation());
        vmenu.add_decrease_hgrilles(corrected_pos(m_le.pos(), 0.25 - 0.5 * (m_le.span() + 1), -m_le.height() / 2 - 0.5, 0.45, m_le.orientation()), m_le.orientation());
    }
}

void Table::spawn_add_element_command()
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
                    m_history.do_command(new AddElementCommand(new RoofElement(pos.v1, pos.v2, pos.v3, orientation, span + 1), m_view));
                else
                    m_history.do_command(new AddElementCommand(new HalfBrickElement(pos.v1, pos.v2 + 0.5, pos.v3), m_view));
            }
        } else if (span == 1) {
            if (same_level)
                if (roof)
                    m_history.do_command(new AddElementCommand(new RoofElement(pos.v1, pos.v2, pos.v3, orientation, span + 1), m_view));
                else
                    m_history.do_command(new AddElementCommand(new BrickElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation), m_view));
                else {
                    orientation = (orientation + 3) & 3;
                    m_history.do_command(new AddElementCommand(new GableBrickElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation), m_view));
                }
        } else {
            if (same_level) {
                if (roof) {
                    m_history.do_command(new AddElementCommand(new RoofElement(pos.v1, pos.v2, pos.v3, orientation, span + 1), m_view));
                } else {
                    if (m_view->span_blocked(pos, span, orientation)) {
                        m_view->mouse_unselect();
                        update();
                    } else {
                        update();
                        m_le.constrain(pos, span, orientation, m_view->gap_below_span(pos, span, orientation), m_view->span_clearance(pos, span, orientation));
                        add_generic_element();
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
        int action_id = m_view->vmenu_item_chosen(e->pos().x(), e->pos().y());
        if (!m_view->get_vmenu().menu_active()) {
            m_view->get_vmenu().clear();
            m_view->mouse_select(e->pos().x(), e->pos().y());
            spawn_add_element_command();
        } else {
            switch (action_id) {
//                case Vmenu::ACTION_FORCE_BRICK:
//                    break;
//                case Vmenu::ACTION_FORCE_WINDOW:
//                    break;
//                case Vmenu::ACTION_FORCE_DOOR:
//                    break;
                case Vmenu::ACTION_INCREASE_HEIGHT:
                    m_history.undo_command();
                    m_le.increase_height();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_DECREASE_HEIGHT:
                    m_history.undo_command();
                    m_le.decrease_height();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_INCREASE_VGRILLES:
                    m_history.undo_command();
                    m_le.increase_vgrilles();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_DECREASE_VGRILLES:
                    m_history.undo_command();
                    m_le.decrease_vgrilles();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_INCREASE_HGRILLES:
                    m_history.undo_command();
                    m_le.increase_hgrilles();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_DECREASE_HGRILLES:
                    m_history.undo_command();
                    m_le.decrease_hgrilles();
                    add_generic_element();
                    break;
                case Vmenu::ACTION_DONE:
                    m_view->get_vmenu().clear();
                    break;
                case Vmenu::ACTION_CANCEL:
                    m_history.undo_command();
                    m_view->get_vmenu().clear();
                    break;

                default:
                    break;
            }

        }
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
    if (!m_view->get_vmenu().menu_active()) {
        if (!m_history.end_of_undo()) {
            m_history.undo_command();
            update();
        } else {
    //        printf("At first command\n");
        }
    }
}

void Table::redo_command()
{
    if (!m_view->get_vmenu().menu_active()) {
        if (!m_history.end_of_redo()) {
            m_history.redo_command();
            update();
        } else {
    //        printf("At last command\n");
        }
    }
}

void Table::new_command()
{
    if (!m_view->get_vmenu().menu_active()) {
        m_history.do_command(new NewCommand(m_view));
        update();
    }
}

void Table::load_command()
{
    if (!m_view->get_vmenu().menu_active()) {
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
}

void Table::save_command()
{
    if (!m_view->get_vmenu().menu_active()) {
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
}

