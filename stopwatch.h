
#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <chrono>

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch();

    void start();
    void stop();
    double elapsed() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_stop;
};

#endif // _STOPWATCH_H_
