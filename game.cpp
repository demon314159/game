
#include "game.h"
#include <stdlib.h>
#include <math.h>

#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QInputDialog>

Game::Game()
{
    initializeWindow();
}

Game::~Game() {
}

void Game::initializeWindow()
{
    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout;

    m_pb1 = new QPushButton(this);
    m_pb2 = new QPushButton(this);
    m_pb3 = new QPushButton(this);
    m_pb4 = new QPushButton(this);
    m_pb5 = new QPushButton(this);
    connect(m_pb1, &QPushButton::clicked, this, &Game::pb1);
    connect(m_pb2, &QPushButton::clicked, this, &Game::pb2);
    connect(m_pb3, &QPushButton::clicked, this, &Game::pb3);
    connect(m_pb4, &QPushButton::clicked, this, &Game::pb4);
    connect(m_pb5, &QPushButton::clicked, this, &Game::pb5);

    layout->addWidget(m_pb1, 0, 0, 1, 1);
    layout->addWidget(m_pb2, 0, 1, 1, 1);
    layout->addWidget(m_pb3, 0, 2, 1, 1);
    layout->addWidget(m_pb4, 0, 3, 1, 1);
    layout->addWidget(m_pb5, 0, 4, 1, 1);

    m_pb1->setText(tr("(N)ew"));
    m_pb2->setText(tr("(L)oad"));
    m_pb3->setText(tr("(S)ave"));
    m_pb4->setText(tr("(U)ndo"));
    m_pb5->setText(tr("(R)edo"));

    m_table = new Table(this);
    layout->addWidget(m_table, 1, 0, 1, 5);

    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Game::pb1()
{
    m_table->new_command();
}

void Game::pb2()
{
    m_table->load_command();
}

void Game::pb3()
{
    m_table->save_command();
}

void Game::pb4()
{
    m_table->undo_command();
}

void Game::pb5()
{
    m_table->redo_command();
}



