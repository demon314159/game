
#ifndef _RISE_PROFILE_H_
#define _RISE_PROFILE_H_

class RiseProfile
{
public:
    RiseProfile(float rise);
    ~RiseProfile();

    float height(float distance, float total_distance) const;
    float pitch(float distance, float total_distance) const;

private:
    float m_rise;
};

#endif // _RISE_PROFILE_H_
