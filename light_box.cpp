//
// light_box.cpp
//
#include "light_box.h"

LightBox::LightBox()
{
    for (int i = 0; i < LIGHTS; i++) {
        m_on_flag[i] = false;
    }
}

LightBox::~LightBox()
{
}

int LightBox::lights() const
{
    return LIGHTS;
}

bool LightBox::is_on(int ix) const
{
    return m_on_flag[ix];
}

bool LightBox::all_on() const
{
    for (int i = 0; i < LIGHTS; i++) {
        if (!m_on_flag[i])
            return false;
    }
    return true;
}

void LightBox::set_on(int ix)
{
    m_on_flag[ix] = true;
}

void LightBox::set_all_off()
{
    for (int i = 0; i < LIGHTS; i++) {
        m_on_flag[i] = false;
    }
}

