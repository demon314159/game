//
// high_score.h
//
#if !defined(_HIGH_SCORE_H_)
#define _HIGH_SCORE_H_

#include <QString>

#define HIGH_SCORE_FILE_NAME "high_score.dat"

class HighScore
{
    static const int MAX_CHARS = 32;

public:
    HighScore();
    ~HighScore();

    int score() const;
    QString name() const;
    void set_high_score(int score, const QString& name);

private:
    int m_score;
    char m_name[MAX_CHARS];
};

#endif // _HIGH_SCORE_H_
