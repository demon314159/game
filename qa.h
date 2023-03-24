
#ifndef _QA_H_
#define _QA_H_

#define QA_START_RENDER 1
#define QA_BEFORE_CLEAR 2
#define QA_AFTER_CLEAR 3
#define QA_BEFORE_SWAP_BUFFERS 4
#define QA_AFTER_SWAP_BUFFERS 5
#define QA_AFTER_FINISH 6


class Qa
{
    static const int BINS = 10000;
public:
    Qa();
    ~Qa();
    void add_sample(int event_id, unsigned long stamp, int frame);

private:
    int m_samples;
    int m_event_id[BINS];
    unsigned long m_stamp[BINS];
    int m_frame[BINS];
};

#endif // _QA_H_
