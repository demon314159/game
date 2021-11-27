
#include "choose.h"
#include "paint_can.h"

Choose::Choose()
    : m_marker_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 2.0))
    , m_first_selected(false)
    , m_second_selected(false)
    , m_first_pos({0.0, 0.0, 0.0})
    , m_second_pos({0.0, 0.0, 0.0})
{
}

Choose::~Choose()
{
}

void Choose::select_no_location()
{
    m_first_selected = false;
    m_second_selected = false;
    m_first_pos = {0.0, 0.0, 0.0};
    m_second_pos = {0.0, 0.0, 0.0};
}

void Choose::select_location(Float3 pos)
{
    printf("choose location (%f, %f, %f)\n", pos.v1, pos.v2, pos.v3);
    if (m_first_selected && !m_second_selected) {
        m_second_selected = true;
        m_second_pos = pos;
    } else {
        m_first_selected = true;
        m_second_selected = false;
        m_first_pos = pos;
        m_second_pos = {0.0, 0.0, 0.0};
    }
}

bool Choose::marker_visible() const
{
    return m_first_selected && !m_second_selected;
}

Float3 Choose::marker_position() const
{
    Float3 pos;
    if (m_first_selected && !m_second_selected)
        pos = m_first_pos;
    else
        pos = {0.0, 0.0, 0.0};
    return pos;
}

const CadModel& Choose::marker_model() const
{
    return m_marker_model;
}

