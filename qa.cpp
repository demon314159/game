
#include "qa.h"
#include "stdio.h"
#include "math.h"

Qa::Qa()
    : m_skip_filter(16)
    , m_samples(0)
{
}

Qa::~Qa()
{
    printf("\nQa report\n");
    double avg_tp = 0.0;
    double min_tp = (double) m_total_period[0];
    double max_tp = (double) m_total_period[0];

    for (int i = 0; i < m_samples; i++) {
//        printf("period %d us\n", m_total_period[i]);
        double samp = (double) m_total_period[i];
        avg_tp += samp;
        min_tp = std::fmin(min_tp, samp);
        max_tp = std::fmax(max_tp, samp);
    }
    if (m_samples > 0) {
        avg_tp /= (double) m_samples;
    }
    printf("samples = %d\n", m_samples);
    printf("avg period = %8.0lf us\n", avg_tp);
    printf("min period = %8.0lf us\n", min_tp);
    printf("max period = %8.0lf us\n", max_tp);
}

void Qa::add_sample(int total_period)
{
    if (m_skip_filter > 0 ) {
        --m_skip_filter;
    } else {
        if (m_samples < BINS) {
            m_total_period[m_samples] = total_period / 1000.0;
            ++m_samples;
        }
    }
}


