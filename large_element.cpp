
#include "large_element.h"
#include <math.h>
#include <algorithm>

#include <stdio.h>


LargeElement::LargeElement()
    : m_position({0.0, 0.0, 0.0})
    , m_span(0)
    , m_height(0)
    , m_orientation(0)
    , m_hgrilles(0)
    , m_vgrilles(0)
    , m_door_flag(false)
    , m_gap_below(false)
    , m_clearance(0)
{
}

LargeElement::~LargeElement()
{
}

void LargeElement::constrain(Float3 position, int span, int orientation, bool gap_below, int clearance)
{
    m_position = position;
    m_span = span;
    m_door_flag = (m_position.v2 < 1.0);
    if (m_door_flag)
        m_height = round((m_span + 1.0) * (4.0 / 2.0) * (3.0 / 2.0)); // 4/2 * 3/2
    else
        m_height = round((m_span + 1.0) * 2.0); // 4/3 * 3/2i
    m_height = std::min(m_height, clearance);

printf("LargeElement:: clearance = %d\n", clearance);

    m_clearance = clearance;
    m_orientation = orientation;
    m_gap_below = gap_below;
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

bool LargeElement::is_gap_below() const
{
    return m_gap_below;
}

void LargeElement::increase_height()
{
    if (m_height < m_clearance)
        ++m_height;
}

void LargeElement::decrease_height()
{
    if (m_height > 1)
        --m_height;
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

