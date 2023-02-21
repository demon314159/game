//
// table.cpp
//
#include "table.h"
#include "look.h"
#include <QMouseEvent>
#include <QFileDialog>

Table::Table(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view(new View())
    , m_timer(new QTimer(this))
{
    setMinimumWidth(600);
    setMinimumHeight(337);
//    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();

    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Table::update));
//    m_timer->start(33);
    m_timer->start(67);
}

Table::~Table()
{
    m_timer->stop();
    delete m_timer;
    makeCurrent();
    delete m_view;
    doneCurrent();
}

void Table::initializeGL()
{
    if (!m_view->initialize())
        close();
    my_update();
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
    QOpenGLWidget::keyPressEvent(e);
    unsigned int a = e->nativeScanCode();
    bool shifted = (e->modifiers() & Qt::ShiftModifier) ? true : false;

    if (a == 0x6f) { // up
        if (shifted) {
            m_view->translate_y(-m_view->height() / 10);
        } else {
            m_view->rotate_ax(-10.0);
        }
        my_update();
    } else if (a == 0x74) { // down
        if (shifted) {
            m_view->translate_y(m_view->height() / 10);
        } else {
            m_view->rotate_ax(10.0);
        }
        my_update();
    } else if (a == 0x71) { // left
        if (shifted) {
            m_view->translate_x(-m_view->width() / 10);
        } else {
            m_view->rotate_ay(-10.0);
        }
        my_update();
    } else if (a == 0x72) { // right
        if (shifted) {
            m_view->translate_x(m_view->width() / 10);
        } else {
            m_view->rotate_ay(10.0);
        }
        my_update();
    } else if (a == 0x1f) { // i or I
        m_view->zoom(3.0 / 2.0);
        my_update();
    } else if (a == 0x20) { // o or O
        m_view->zoom(2.0 / 3.0);
        my_update();
    } else if (a == 0x2b) { // h or H
        m_view->zoom_home();
        if (shifted) {
            m_view->rotate_home();
            m_view->translate_home();
        }
        m_navigate.stop();
        my_update();
    }
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
    if (e->button() == Qt::MiddleButton) {
        m_view->zoom_home();
        m_view->rotate_home();
        m_view->translate_home();
        m_navigate.stop();
        my_update();
    } else if (e->button() == Qt::LeftButton) {
        m_navigate.start_rotate(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
        m_navigate.start_translate(e->pos().x(), e->pos().y());
    }
    QOpenGLWidget::mousePressEvent(e);
}

void Table::mouse_navigate(QMouseEvent* e)
{
    if (m_navigate.is_rotate()) {
        float degx, degy;
        if (m_navigate.rotate_threshold_exceeded(e->pos().x(), e->pos().y(), degx, degy)) {
            m_view->rotate_ay(degx);
            m_view->rotate_ax(degy);
            my_update();
        }
    } else if (m_navigate.is_translate()) {
        int dx, dy;
        if (m_navigate.translate_threshold_exceeded(e->pos().x(), e->pos().y(), dx, dy)) {
            m_view->translate_x(dx);
            m_view->translate_y(dy);
            my_update();
        }

    }
}

void Table::mouseMoveEvent(QMouseEvent* e)
{
//    printf("  mouse move %d, %d\n", e->pos().x(), e->pos().y());
    if (m_navigate.active())
        mouse_navigate(e);
    QOpenGLWidget::mouseMoveEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
//        printf("  mouse release %d, %d\n", e->pos().x(), e->pos().y());
        if (m_navigate.active())
            mouse_navigate(e);
        m_navigate.stop();
    } else if (e->button() == Qt::RightButton) {
        if (m_navigate.active())
            mouse_navigate(e);
         m_navigate.stop();
    }
    QOpenGLWidget::mouseReleaseEvent(e);
}

void Table::wheelEvent(QWheelEvent* e)
{
    int angle = e->angleDelta().y();
    if (angle > 0) {
        m_view->zoom(3.0 / 2.0);
        my_update();
    }
    if (angle < 0) {
        m_view->zoom(2.0 / 3.0);
        my_update();
    }
    e->accept();
}

void Table::my_update()
{
//    update();
}
