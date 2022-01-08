
#include "choose.h"
#include "paint_can.h"
#include "math.h"

Choose::Choose()
    : m_marker_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 2.0))
    , m_first_selected(false)
    , m_second_selected(false)
    , m_first_choice({{0.0, 0.0, 0.0}, false, 0})
    , m_second_choice({{0.0, 0.0, 0.0}, false, 0})
{
}

Choose::~Choose()
{
}

void Choose::select_no_choice()
{
    m_first_selected = false;
    m_second_selected = false;
    m_first_choice = {{0.0, 0.0, 0.0}, false, 0};
    m_second_choice = {{0.0, 0.0, 0.0}, false, 0};
}

void Choose::select_choice(Choice c)
{
    if (m_first_selected && !m_second_selected) {
        m_second_selected = true;
        m_second_choice = c;
    } else {
        m_first_selected = true;
        m_second_selected = false;
        m_first_choice = c;
        m_second_choice = {{0.0, 0.0, 0.0}, false, 0};
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
    return m_first_choice.gable ? 33.69 : 0.0;
}

int Choose::marker_orientation() const
{
    return m_first_choice.orientation;
}

const CadModel& Choose::marker_model() const
{
    return m_marker_model;
}

bool Choose::new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool& roof)
{
    roof = false;
    if (m_first_selected && m_second_selected) {
        printf("1st height = %f, 2nd height = %f\n", m_first_choice.position.v2, m_second_choice.position.v2);
        same_level = m_first_choice.position.v2 == m_second_choice.position.v2;
        if (same_level) {
            pos.v1 = (m_first_choice.position.v1 + m_second_choice.position.v1) / 2.0;
            pos.v2 = (m_first_choice.position.v2 + m_second_choice.position.v2) / 2.0;
            pos.v3 = (m_first_choice.position.v3 + m_second_choice.position.v3) / 2.0;

            if (m_first_choice.gable || m_second_choice.gable) {
                if (m_first_choice.gable && m_second_choice.gable && m_first_choice.orientation == m_second_choice.orientation) {
                    roof = true;
                    printf("Roof element selected\n");
                } else {
                    printf("Roof elemwnt Rejected because of same level mixed gable activity\n");
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

            if (m_first_choice.gable) {
                printf("Rejected because of different level first gable activity\n");
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
                if (m_second_choice.position.v2 < m_first_choice.position.v2)
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
