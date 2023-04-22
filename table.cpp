//
// table.cpp
//
#include "table.h"
#include <QPainter>
#include <QMessageBox>
#include <math.h>
#include <algorithm>

Table::Table(PuzzleBook* puzzle_book, const ShapeSet* shape_set, QPushButton* previous_button, QPushButton* next_button, QPushButton* clear_button, QWidget *parent)
    : QWidget(parent)
    , m_parent(parent)
    , m_previous_button(previous_button)
    , m_next_button(next_button)
    , m_clear_button(clear_button)
    , m_puzzle_book(puzzle_book)
    , m_scene(puzzle_book, shape_set)
{
    setCursor(Qt::PointingHandCursor);
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
//    painter.fillRect(painter.viewport(), QColor(102, 204, 255));
    painter.fillRect(painter.viewport(), QColor(76, 153, 191));
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
    m_scene.mouse_wheel(e->position().x(), e->position().y(), angle > 0);
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
    m_clear_button->setEnabled(!m_puzzle_book->current_challenge_solved());
}

void Table::clear_board()
{
    m_scene.clear_board();
    full_update();
}

void Table::show_help()
{
    QMessageBox msg_box;
    msg_box.setText(
"<h2>How To Play</h2>"
"<p>Use the <b>left</b> mouse button to <b>drag</b> pieces on and off the red tray.</p>"
"<p>A piece may be <b>rotated</b> or <b>reflected</b> when it is not on the tray.</p>"
"<p>The <b>scroll wheel</b> will <b>rotate</b> a nearby piece.</p>"
"<p>The <b>right</b> mouse button will <b>reflect</b> a nearby piecee.</p>"
"<p>Each <b>challenge</b> is solved when all of the pieces have been placed in the red tray.</p>"
"<p>Once a <b>challenge</b> has been solved, the <b>next challenge</b> becomes available.</p>"
"<p>Complete all 48 <b>challenges</b> to finish the game.</p>"
"<p>Some <b>challenges</b> have <i>pre-assigned</i> <b>hint</b> pieces that are locked in position.</p>"
"<h2>About</h2>"
"<p>These puzzles are drawn from a 1960's game called <i><b>Spear's Multipuzzle.</b></i>"
"  The physical game is still available at auction sites but it is very tedious to set up each challenge."
"  This software removes the tedious set-up and offers the user only the fun puzzle solving."
"<p>Created 2023-Jan-8 by Andy Summers (<i>demon314159@github)</i><p>"
);
    msg_box.exec();
}
