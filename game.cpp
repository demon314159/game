
#include "game.h"
#include <stdlib.h>
#include <math.h>

#include <QStackedWidget>
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QInputDialog>
#include "table.h"

Game::Game(int view_ix)
    : m_view_ix(view_ix)
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
    m_label = new QLabel(this);
    connect(m_pb1, &QPushButton::clicked, this, &Game::pb1);



    layout->addWidget(m_pb1, 0, 0, 1, 1);
    layout->addWidget(m_label, 0, 2, 1, 2);

    m_pb1->setText(tr("(N)ew Game"));
    high_score_message();

    m_stacked_widget = new QStackedWidget;
    m_table = new Table(m_view_ix, m_mvp_matrix, m_rot_matrix, m_image_set, m_stacked_widget, this);
    m_alt_table = new AltTable(m_mvp_matrix, m_rot_matrix, m_image_set, m_stacked_widget, this);
    connect(m_alt_table, &AltTable::game_over, this, &Game::game_over);
    connect(this, &Game::new_game_ready, m_alt_table, &AltTable::new_game_ready);
    m_stacked_widget->addWidget(m_table);
    m_stacked_widget->addWidget(m_alt_table);
    layout->addWidget(m_stacked_widget, 1, 0, 1, 5);

    layout->setRowStretch(1, 1);

    window->setLayout(layout);
    setCentralWidget(window);
    window->show();
}

void Game::high_score_message()
{
    if (m_high_score.score() <= 0)
        m_label->setText("No high score yet");
    else
        m_label->setText(QString("H I G H   S C O R E :  %2  %1").arg(m_high_score.name()).arg(m_high_score.score()));
}

void Game::pb1()
{
    m_alt_table->new_game();
}

void Game::game_over(int score)
{
    if (score > m_high_score.score()) {
        QString text = QInputDialog::getText(this, QString("High Score %1 ").arg(score),
                       "Enter Name", QLineEdit::Normal, m_high_score.name());
        m_high_score.set_high_score(score, text);
        high_score_message();
    }
    emit(new_game_ready());
}


