
#include "navigate.h"
#include <math.h>

Navigate::Navigate()
    : m_rotate(false)
    , m_translate(false)
    , m_sx(0)
    , m_sy(0)
{
}

Navigate::~Navigate()
{
}

void Navigate::start_rotate(int sx, int sy)
{
    m_sx = sx;
    m_sy = sy;
    m_rotate = true;
}

void Navigate::start_translate(int sx, int sy)
{
    m_sx = sx;
    m_sy = sy;
    m_translate = true;
}

void Navigate::stop()
{
    m_rotate = false;
    m_translate = false;
    m_sx = 0;
    m_sy = 0;
}

bool Navigate::active() const
{
    return m_rotate || m_translate;
}

bool Navigate::is_rotate() const
{
    return m_rotate;
}

bool Navigate::is_translate() const
{
    return m_translate;
}

bool Navigate::rotate_threshold_exceeded(int sx, int sy, float& degx, float& degy)
{
    float threshold = 5.0;
    float dx = 0.2 * (sx - m_sx);
    float dy = 0.2 * (sy - m_sy);
    degx = round(dx);
    degy = round(dy);
    if (fabs(degx) > threshold || fabs(degy) > threshold) {
        m_sx = sx;
        m_sy = sy;
        return true;
    }
    return false;
}

bool Navigate::translate_threshold_exceeded(int sx, int sy, int& dx, int& dy)
{
    int threshold = 8;
    dx = sx - m_sx;
    dy = sy - m_sy;
    if (abs(dx) > threshold || abs(dy) > threshold) {
        m_sx = sx;
        m_sy = sy;
        return true;
    }
    return false;
}
