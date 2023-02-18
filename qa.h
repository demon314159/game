
#ifndef _QA_H_
#define _QA_H_

class Qa
{
    static const int BINS = 1000;
public:
    Qa();
    ~Qa();
    void add_sample(int total_period);

private:
    int m_skip_filter;
    int m_samples;
    int m_total_period[BINS];
};

#endif // _QA_H_
