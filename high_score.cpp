//
// high_score.cpp
//
#include "high_score.h"

HighScore::HighScore()
    : m_score(0)
    , m_name("no high score yet")
{
    // read_from_file
}

HighScore::~HighScore()
{
}

int HighScore::score() const
{
    return m_score;
}

QString HighScore::name() const
{
    return m_name;
}

void HighScore::set_high_score(int score, const QString& name)
{
    if (score > m_score) {
        m_score = score;
        m_name = name;
//        write_to_file();
    }
}

