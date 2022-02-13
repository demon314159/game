
#include "navigate.h"
#include <math.h>

Navigate::Navigate()
    : m_active(false)
    , m_sx(0)
    , m_sy(0)
{
}

Navigate::~Navigate()
{
}

void Navigate::start(int sx, int sy)
{
    m_sx = sx;
    m_sy = sy;
    m_active = true;
}

void Navigate::stop()
{
    m_active = false;
    m_sx = 0;
    m_sy = 0;
}

bool Navigate::active() const
{
    return m_active;
}

bool Navigate::threshold_exceeded(int sx, int sy, float& degx, float& degy)
{
    float threshold = 10.0;
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

