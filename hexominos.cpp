
#include "hexominos.h"
#include <stdlib.h>
#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include "table.h"

Hexominos::Hexominos(const FullSet* full_set, const PuzzleBook* puzzle_book)
    : m_full_set(full_set)
    , m_puzzle_book(puzzle_book)
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
    m_pb1->setText(tr("Button 1"));
    m_pb2->setText(tr("Button 2"));
    m_pb3->setText(tr("Button 3"));
    m_pb4->setText(tr("Button 4"));
    m_pb5->setText(tr("Button 5"));

    m_table = new Table(this);
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

