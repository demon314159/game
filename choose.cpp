
#include "choose.h"
#include "paint_can.h"
#include "math.h"

Choose::Choose()
    : m_marker1_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 2.0))
    , m_marker2_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 3.0))
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
//    printf("choose location (%f, %f, %f)\n", pos.v1, pos.v2, pos.v3);
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

bool Choose::marker1_visible() const
{
    return m_first_selected || m_second_selected;
}

bool Choose::marker2_visible() const
{
    return m_first_selected && m_second_selected;
}

Float3 Choose::marker1_position() const
{
    return m_first_pos;
}

Float3 Choose::marker2_position() const
{
    return m_second_pos;
}

const CadModel& Choose::marker1_model() const
{
    return m_marker1_model;
}

const CadModel& Choose::marker2_model() const
{
    return m_marker2_model;
}

bool Choose::new_element_chosen(Float3& pos, int& span, int& orientation)
{
    if (m_first_selected && m_second_selected) {
        if (m_first_pos.v2 == m_second_pos.v2) {
            pos.v1 = (m_first_pos.v1 + m_second_pos.v1) / 2.0;
            pos.v2 = (m_first_pos.v2 + m_second_pos.v2) / 2.0;
            pos.v3 = (m_first_pos.v3 + m_second_pos.v3) / 2.0;
            if (m_first_pos.v1 == m_second_pos.v1) {
                orientation = m_first_pos.v3 < m_second_pos.v3 ? 3 : 1;
                span = round(fabs(m_first_pos.v3 - m_second_pos.v3));
                return true;
            } else if (m_first_pos.v3 == m_second_pos.v3) {
                orientation = m_first_pos.v1 < m_second_pos.v1 ? 0 : 2;
                span = round(fabs(m_first_pos.v1 - m_second_pos.v1));
                return true;
            }
            select_no_location();
            return false;
        } else {
            select_no_location();
            return false;
        }

    } else {
        return false;
    }
}
