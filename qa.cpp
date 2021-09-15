
#include "qa.h"
#include "stdio.h"

Qa::Qa()
  : m_primed(false)
  , m_last_time(0)
{
    for (int i = 0; i < BINS; i++) {
        m_hist[i] = 0;
    }
}

Qa::~Qa()
{
    printf("\nQa report\n");
    for (int i = 0; i < BINS; i++) {
        if (m_hist[i] > 0) {
            printf("%4d : %d\n", i, m_hist[i]);
        }
    }
}

void Qa::add_sample(int ms_time)
{
    if (m_primed) {
        int ms_dt = ms_time - m_last_time;
        if (ms_dt < 0)
            ms_dt = 0;
        if (ms_dt >= BINS)
            ms_dt = BINS - 1;
        ++m_hist[ms_dt];
    }
    m_last_time = ms_time;
    m_primed = true;
}


