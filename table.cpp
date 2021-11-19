//
// table.cpp
//
#include "table.h"
#include <QMouseEvent>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view(new View(new Document(QString("house.txt"))))
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
        if (!m_history.end_of_undo()) {
            m_history.undo_command();
            update();
        } else
            printf("At first command\n");
    } else if (a == 0x1b) { // r or R
        if (!m_history.end_of_redo()) {
            m_history.redo_command();
            update();
        } else
            printf("At last command\n");
    } else if (a == 0x36) { // c or C
        if (shifted) {
            if (m_view->get_doc()->elements() > 0) {
                m_history.do_command(new RemoveElementCommand(0, m_view));
            } else {
                printf("no more elements\n");
            }
        }
        else
          m_history.do_command(new AddElementCommand(new BrickElement(0.0, 10.0, 0.0, 0), m_view));
        update();
    } else if (a == 0x2e) { // l or L
          m_history.do_command(new LoadCommand(QString("other_house.txt"), m_view));
          update();
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

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_view->mouse_select(e->pos().x(), e->pos().y());
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

