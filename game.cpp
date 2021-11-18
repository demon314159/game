
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
    connect(m_pb1, &QPushButton::clicked, this, &Game::pb1);

    layout->addWidget(m_pb1, 0, 0, 1, 1);

    m_pb1->setText(tr("button"));

    m_table = new Table(this);
    layout->addWidget(m_table, 1, 0, 1, 5);

    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Game::pb1()
{
}



