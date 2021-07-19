//
// high_score.h
//
#if !defined(_HIGH_SCORE_H_)
#define _HIGH_SCORE_H_

#include <QString>

class HighScore
{
    const QString file_name = "high_score.dat";

public:
    HighScore();
    ~HighScore();

    int score() const;
    QString name() const;
    void set_high_score(int score, const QString& name);

private:
    int m_score;
    QString m_name;
};

#endif // _HIGH_SCORE_H_
