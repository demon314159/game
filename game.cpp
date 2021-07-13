
#include "game.h"
#include <stdlib.h>
#include <math.h>

#include <QStackedWidget>
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include "table.h"

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
    m_pb1->setText(tr("Button 1"));
    m_pb2->setText(tr("Button 2"));
    m_pb3->setText(tr("Button 3"));
    m_pb4->setText(tr("Button 4"));
    m_pb5->setText(tr("Button 5"));

    m_stacked_widget = new QStackedWidget;
    m_table = new Table(m_mvp_matrix, m_rot_matrix, m_image_set, m_stacked_widget, this);
    m_alt_table = new AltTable(m_mvp_matrix, m_rot_matrix, m_image_set, m_stacked_widget, this);
    m_stacked_widget->addWidget(m_table);
    m_stacked_widget->addWidget(m_alt_table);
    layout->addWidget(m_stacked_widget, 1, 0, 1, 5);

    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Game::pb1()
{
}

void Game::pb2()
{
}

void Game::pb3()
{
}

void Game::pb4()
{
}

void Game::pb5()
{
}

