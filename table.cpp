//
// table.cpp
//
#include "table.h"
#include <QMouseEvent>
#include <QFileDialog>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view(new View(new Document(QString("house.brk"))))
{
    setMinimumWidth(600);
    setMinimumHeight(337);
    setFocusPolicy(Qt::StrongFocus);
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

void Table::spawn_add_element_command()
{
        Float3 pos;
        int span;
        int orientation;
        if (m_view->new_element_chosen(pos, span, orientation)) {
            if (span == 0) {
                m_history.do_command(new AddElementCommand(new HalfBrickElement(pos.v1, pos.v2 + 0.5, pos.v3), m_view));
            } else if (span == 1) {
                m_history.do_command(new AddElementCommand(new BrickElement(pos.v1, pos.v2 + 0.5, pos.v3, orientation), m_view));
            } else {
                printf("Adding element of span %d ?\n", span);
            }
        }
}

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_view->mouse_select(e->pos().x(), e->pos().y());
        spawn_add_element_command();
        update();
    } else if (e->button() == Qt::RightButton) {
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
    QString file_name = QFileDialog::getOpenFileName(NULL,
        tr("Open Brick File"), "", tr("BRK Files (*.brk)"));
    if (file_name.length() == 0) {
        printf("No file selected\n");
        return;
    }
    m_history.do_command(new LoadCommand(file_name, m_view));
    update();
}

void Table::save_command()
{
    QString file_name = QFileDialog::getSaveFileName(NULL,
            tr("Save Brick File"), "", tr("BRK Files (*.brk)"));
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

