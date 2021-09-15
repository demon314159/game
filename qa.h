
#ifndef _QA_H_
#define _QA_H_

class Qa
{
    static const int BINS = 1000;
public:
    Qa();
    ~Qa();
    void add_sample(int ms_time);

private:
    bool m_primed;
    int m_last_time;
    int m_hist[BINS];
};

#endif // _QA_H_
