//
// high_score.cpp
//
#include "high_score.h"
#include <sys/stat.h>

HighScore::HighScore()
{
    m_score = 0;
    m_name[0] = 0;
    FILE* ffi = fopen(HIGH_SCORE_FILE_NAME, "r");
    if (ffi == NULL) {
        return;
    }
    if (1 != fread(this, sizeof(HighScore), 1, ffi) ) {
        m_score = 0;
        m_name[0] = 0;
    }
    fclose(ffi);
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
    return QString(m_name);
}

void HighScore::set_high_score(int score, const QString& name)
{
    if (score > m_score) {
        m_score = score;
        int len = std::min(MAX_CHARS - 1, (int) name.length());
        for (int i = 0; i < len; i++) {
            m_name[i] = name.toLatin1().data()[i];
        }
        m_name[len] = 0;
        FILE* ffo = fopen(HIGH_SCORE_FILE_NAME, "w");
        if (ffo == NULL)
            return;
        fwrite(this, sizeof(HighScore), 1, ffo);
        fclose(ffo);
    }
}

