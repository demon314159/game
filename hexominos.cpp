
#include "hexominos.h"
#include <stdlib.h>
#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include "table.h"

Hexominos::Hexominos(PuzzleBook* puzzle_book, ShapeSet* shape_set)
    : m_puzzle_book(puzzle_book)
    , m_shape_set(shape_set)
    , m_history(puzzle_book, shape_set)
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
    m_pb4->setText(tr("Undo"));
    m_pb5->setText(tr("Redo"));

    m_table = new Table(m_puzzle_book, m_shape_set, &m_history, this);
    layout->addWidget(m_table, 1, 0, 1, 5);
    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Hexominos::pb1()
{
}

void Hexominos::pb2()
{
}

void Hexominos::pb3()
{
}

void Hexominos::pb4()
{
}

void Hexominos::pb5()
{
}

