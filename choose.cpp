
#include "choose.h"
#include "paint_can.h"
#include "math.h"
#include "element.h"

Choose::Choose()
    : m_marker_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 2.0))
    , m_first_selected(false)
    , m_second_selected(false)
    , m_first_choice({{0.0, 0.0, 0.0}, 0, 0})
    , m_second_choice({{0.0, 0.0, 0.0}, 0, 0})
{
}

Choose::~Choose()
{
}

void Choose::select_no_choice()
{
    m_first_selected = false;
    m_second_selected = false;
    m_first_choice = {{0.0, 0.0, 0.0}, 0, 0};
    m_second_choice = {{0.0, 0.0, 0.0}, 0, 0};
}

void Choose::select_choice(Choice c)
{
    if (m_first_selected && !m_second_selected) {
        m_second_selected = true;
        m_second_choice = c;
    } else {
        if (c.kind == ELEMENT_ROOF) {
            select_no_choice();
        } else {
            m_first_selected = true;
            m_second_selected = false;
            m_first_choice = c;
            m_second_choice = {{0.0, 0.0, 0.0}, 0, 0};
        }
    }
}

bool Choose::marker_visible() const
{
    return m_first_selected || m_second_selected;
}

Float3 Choose::marker_position() const
{
    return m_first_choice.position;
}

float Choose::marker_angle() const
{
    return m_first_choice.kind == ELEMENT_GABLE_BRICK ? 33.69 : 0.0;
}

int Choose::marker_orientation() const
{
    return m_first_choice.orientation;
}

const CadModel& Choose::marker_model() const
{
    return m_marker_model;
}

bool Choose::new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool &roof)
{
    if (m_first_selected && m_second_selected) {
        same_level = m_first_choice.position.v2 == m_second_choice.position.v2;
        if (same_level) {
            pos.v1 = (m_first_choice.position.v1 + m_second_choice.position.v1) / 2.0;
            pos.v2 = (m_first_choice.position.v2 + m_second_choice.position.v2) / 2.0;
            pos.v3 = (m_first_choice.position.v3 + m_second_choice.position.v3) / 2.0;

            roof = m_first_choice.kind == ELEMENT_GABLE_BRICK && m_second_choice.kind == ELEMENT_GABLE_BRICK;

            if ((m_first_choice.kind == ELEMENT_GABLE_BRICK) || (m_second_choice.kind == ELEMENT_GABLE_BRICK)) {
                if (roof && (m_first_choice.orientation != m_second_choice.orientation)) {
                    select_no_choice();
                    return false;
                }
            }
            if (m_first_choice.position.v1 == m_second_choice.position.v1) {
                if (roof)
                    orientation = m_first_choice.orientation;
                else
                    orientation = m_first_choice.position.v3 < m_second_choice.position.v3 ? 3 : 1;
                span = round(fabs(m_first_choice.position.v3 - m_second_choice.position.v3));
                return true;
            } else if (m_first_choice.position.v3 == m_second_choice.position.v3) {
                if (roof)
                    orientation = m_first_choice.orientation;
                else
                    orientation = m_first_choice.position.v1 < m_second_choice.position.v1 ? 0 : 2;
                span = round(fabs(m_first_choice.position.v1 - m_second_choice.position.v1));
                return true;
            }
            select_no_choice();
            return false;
        } else { // Different levels
            if (m_first_choice.kind == ELEMENT_GABLE_BRICK) {
                select_no_choice();
                return false;
            }
            pos = m_first_choice.position;
            if (m_first_choice.position.v1 == m_second_choice.position.v1) {
                orientation = m_first_choice.position.v3 < m_second_choice.position.v3 ? 3 : 1;
                span = round(fabs(m_first_choice.position.v3 - m_second_choice.position.v3));
            } else if (m_first_choice.position.v3 == m_second_choice.position.v3) {
                orientation = m_first_choice.position.v1 < m_second_choice.position.v1 ? 0 : 2;
                span = round(fabs(m_first_choice.position.v1 - m_second_choice.position.v1));
            } else {
                select_no_choice();
                return false;
            }
            if (span == 1) {
                float sch = m_second_choice.position.v2;
                if (m_second_choice.kind == ELEMENT_ROOF)
                    sch -= 1.0;
                if (sch < m_first_choice.position.v2)
                    orientation = (orientation + 2) & 3;
                return true;
            }
            select_no_choice();
            return false;
        }
    } else {
        return false;
    }
}
