
#include "hexominos.h"
#include <stdlib.h>
#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QMessageBox>
#include "table.h"

Hexominos::Hexominos(PuzzleBook* puzzle_book, ShapeSet* shape_set)
    : m_puzzle_book(puzzle_book)
    , m_shape_set(shape_set)
{
    initializeWindow();
}

Hexominos::~Hexominos() {
}

void Hexominos::initializeWindow()
{
    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout;

    m_pb1 = new QPushButton(this);
    m_pb2 = new QPushButton(this);
    m_pb3 = new QPushButton(this);
    m_pb4 = new QPushButton(this);
    m_pb5 = new QPushButton(this);
    connect(m_pb1, &QPushButton::clicked, this, &Hexominos::pb1);
    connect(m_pb2, &QPushButton::clicked, this, &Hexominos::pb2);
    connect(m_pb3, &QPushButton::clicked, this, &Hexominos::pb3);
    connect(m_pb4, &QPushButton::clicked, this, &Hexominos::pb4);
    connect(m_pb5, &QPushButton::clicked, this, &Hexominos::pb5);
    layout->addWidget(m_pb1, 0, 0, 1, 1);
    layout->addWidget(m_pb2, 0, 1, 1, 1);
    layout->addWidget(m_pb3, 0, 2, 1, 1);
    layout->addWidget(m_pb4, 0, 3, 1, 1);
    layout->addWidget(m_pb5, 0, 4, 1, 1);
    m_pb1->setText(tr("Previous Challenge"));
    m_pb2->setText(tr("Next Challenge"));
    m_pb3->setText(tr(" "));
    m_pb3->hide();
    m_pb4->setText(tr("Clear Board"));
    m_pb5->setText(tr("Help"));

    m_table = new Table(m_puzzle_book, m_shape_set, m_pb1, m_pb2, this);
    layout->addWidget(m_table, 1, 0, 1, 5);
    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Hexominos::pb1()
{
    m_table->pb_previous_challenge();
}

void Hexominos::pb2()
{
    m_table->pb_next_challenge();
}

void Hexominos::pb3()
{
}

void Hexominos::pb4()
{
    m_table->clear_board();
}

void Hexominos::pb5()
{
    QMessageBox msg_box;
    msg_box.setText(
"<h2>Basic Rules</h2>"
"<p>Use the <b>left</b> mouse button to <b>drag</b> pieces on and off the red tray.</p>"
"<p>A piece may be <b>rotated</b> or <b>reflected</b> when it is not on the tray.</p>"
"<p>The <b>scroll wheel</b> will <b>rotate</b> a nearby piece.</p>"
"<p>The <b>right</b> mouse button will <b>reflect</b> a nearby piecee.</p>"
"<p>Each <b>challenge</b> is solved when all of the pieces have been placed in the red tray.</p>"
"<p>Once a <b>challenge</b> has been solved, the <b>next challenge</b> becomes available.</p>"
"<p>Complete all 48 <b>challenges</b> to finish the game.</p>"
"<p>Some <b>challenges</b> are made easier by having pre-assigned <b>hint</b> pieces that can't be removed from the red tray</p>"
"<h2>About</h2>"
"<p>These puzzles are drawn from a 1960's game called <i><b>Spear's Multipuzzle.</b></i>"
"  The physical game is still available at auction sites but it is very tedious to set up each challenge."
"  This software removes the tedious set-up and offers the user only the fun puzzle solving."
"<p>Created 2023-Jan-8 by Andy Summers (<i>demon314159@github)</i><p>"
);
    msg_box.exec();
}

