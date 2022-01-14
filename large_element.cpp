
#include "large_element.h"
#include <math.h>

LargeElement::LargeElement()
    : m_position({0.0, 0.0, 0.0})
    , m_span(0)
    , m_height(0)
    , m_orientation(0)
    , m_hgrilles(0)
    , m_vgrilles(0)
    , m_door_flag(false)
{
}

LargeElement::~LargeElement()
{
}

void LargeElement::constrain(Float3 position, int span, int orientation)
{
    m_position = position;
    m_span = span;
    m_door_flag = (m_position.v2 < 1.0);
    if (m_door_flag)
        m_height = (float) round((m_span + 1.0) * (4.0 / 2.0) * (3.0 / 2.0)); // 4/2 * 3/2
    else
        m_height = (float) round((m_span + 1.0) * 2.0); // 4/3 * 3/2
    m_orientation = orientation;
    m_vgrilles = 1;
    m_hgrilles = 2;
}

Float3 LargeElement::pos() const
{
    return m_position;
}

int LargeElement::span() const
{
    return m_span;
}

int LargeElement::height() const
{
    return m_height;
}

int LargeElement::orientation() const
{
    return m_orientation;
}

int LargeElement::hgrilles() const
{
    return m_hgrilles;
}

int LargeElement::vgrilles() const
{
    return m_vgrilles;
}

bool LargeElement::is_door() const
{
    return m_door_flag;
}

void LargeElement::bigger()
{
    ++m_height;
}

void LargeElement::smaller()
{
    if (m_height > 3.0) {
        --m_height;
    }
}

void LargeElement::increase_vgrilles()
{
    ++m_vgrilles;
}

void LargeElement::decrease_vgrilles()
{
    if (m_vgrilles > 0) {
        --m_vgrilles;
    }
}

void LargeElement::increase_hgrilles()
{
    ++m_hgrilles;
}

void LargeElement::decrease_hgrilles()
{
    if (m_hgrilles > 0) {
        --m_hgrilles;
    }
}

void LargeElement::flip()
{
    m_orientation = (m_orientation + 2) & 3;
}

