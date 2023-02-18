
#include "qa.h"
#include "stdio.h"

Qa::Qa()
    : m_skip_filter(16)
    , m_samples(0)
{
}

Qa::~Qa()
{
    printf("\nQa report\n");
    double avg_tp = 0.0;
    double avg_rt = 0.0;
    for (int i = 0; i < m_samples; i++) {
        printf("period %d us, render_time %d us\n", m_total_period[i], m_render_time[i]);
        avg_tp += (double) m_total_period[i];
        avg_rt += (double) m_render_time[i];
    }
    if (m_samples > 0) {
        avg_tp /= (double) m_samples;
        avg_rt /= (double) m_samples;
    }
    printf("avg period = %8.0lf,  avg render_time = %8.0lf\n", avg_tp, avg_rt);
}

void Qa::add_sample(int total_period, int render_time)
{
    if (m_skip_filter > 0 ) {
        --m_skip_filter;
    } else {
        if (m_samples < BINS) {
            m_total_period[m_samples] = total_period / 1000.0;
            m_render_time[m_samples] = render_time / 1000.0;
            ++m_samples;
        }
    }
}


