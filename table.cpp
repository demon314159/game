//
// table.cpp
//
#include "table.h"
#include <QPainter>
#include <math.h>
#include <algorithm>

Table::Table(PuzzleBook* puzzle_book, const ShapeSet* shape_set, QPushButton* previous_button, QPushButton* next_button, QWidget *parent)
    : QWidget(parent)
    , m_parent(parent)
    , m_previous_button(previous_button)
    , m_next_button(next_button)
    , m_puzzle_book(puzzle_book)
    , m_scene(puzzle_book, shape_set)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(480);
    setMinimumWidth(640);
    full_update();
}

int Table::text_width(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.width();
}

int Table::text_height(QPainter& painter, const QString &s)
{
    QRect rect = painter.boundingRect(0, 0, 0, 0, 0, s);
    return rect.height();
}

void Table::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);
//    int th = text_height(painter, QString("0"));

    m_scene.draw(painter);
}

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_scene.mouse_left_press(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
        m_scene.mouse_right_press(e->pos().x(), e->pos().y());
    }
    full_update();
    QWidget::mousePressEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_scene.mouse_left_release(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
    }
    full_update();
    QWidget::mouseReleaseEvent(e);
}

void Table::mouseMoveEvent(QMouseEvent* e)
{
    m_scene.mouse_move(e->pos().x(), e->pos().y());
    full_update();
    QWidget::mouseMoveEvent(e);
}

void Table::wheelEvent(QWheelEvent* e)
{
    int angle = e->angleDelta().y();
    m_scene.mouse_wheel(e->pos().x(), e->pos().y(), angle > 0);
    full_update();
    e->accept();
}

void Table::pb_next_challenge()
{
    m_scene.pb_next_challenge();
    full_update();
}

void Table::pb_previous_challenge()
{
    m_scene.pb_previous_challenge();
    full_update();
}

void Table::full_update()
{
    update();
    m_parent->setWindowTitle(QString("Hexominos: Challenge %1 of %2").arg(m_puzzle_book->current_challenge() + 1).arg(m_puzzle_book->challenges()));
    m_previous_button->setEnabled(m_puzzle_book->current_challenge() > 0);
    m_next_button->setEnabled(m_puzzle_book->current_challenge_solved() && (m_puzzle_book->current_challenge() < (m_puzzle_book->challenges() - 1)));
}

void Table::clear_board()
{
    m_scene.clear_board();
    full_update();
}
