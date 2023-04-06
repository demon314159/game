
#include "rise_profile.h"
#include "pi.h"
#include "math.h"

RiseProfile::RiseProfile(float rise)
    : m_rise(rise)
{
}

RiseProfile::~RiseProfile()
{
}

float RiseProfile::height(float distance, float total_distance) const
{
    float angle = -PI / 2.0 + PI * distance / total_distance;
    return m_rise * (0.5 + 0.5 * sin(angle));
}

float RiseProfile::pitch(float distance, float total_distance) const
{

    float angle = -PI / 2.0 + PI * distance / total_distance;
    float slope = (m_rise / 2.0) * (PI / total_distance) * cos(angle);
    return (-180.0 / PI) * atan2(slope, 1.0);
}
