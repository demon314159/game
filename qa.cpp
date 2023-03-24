
#include "qa.h"
#include "stdio.h"
#include "math.h"

Qa::Qa()
    : m_samples(0)
{
}

Qa::~Qa()
{
    printf("\nQa report based on %d samples\n", m_samples);
    if (m_samples > 0) {
        int current_frame = m_frame[0];
        unsigned long base = m_stamp[0];
        double period = 1.0e9 * 2.0 / 60.0;
        for (int i = 0; i < m_samples; i++) {
            if (current_frame != m_frame[i]) {
                current_frame = m_frame[i];
//                printf("\n%lf\n", this_stamp - last_stamp);
                printf("\n");
            }
            double a = (double) (m_stamp[i] - base);
            double dstamp =  0.01 + a / period;
            if (m_event_id[i] == QA_START_RENDER) {
                printf("(%6.3lf), ", round(dstamp));
            }
            printf("%6.3lf, ", dstamp);

        }
    }
}

void Qa::add_sample(int event_id, unsigned long stamp, int frame)
{
    if (m_samples < BINS) {
        m_event_id[m_samples] = event_id;
        m_stamp[m_samples] = stamp;
        m_frame[m_samples] = frame;
        ++m_samples;
    }
}


