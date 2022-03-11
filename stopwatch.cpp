
#include "stopwatch.h"

Stopwatch::Stopwatch()
{
    start();
    stop();
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

void Stopwatch::stop()
{
    m_stop = std::chrono::high_resolution_clock::now();
}

double Stopwatch::elapsed() const
{
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(m_stop - m_start);
    double et = elapsed.count() * 1e-9;
    return et;
}


