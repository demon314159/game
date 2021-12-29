
#ifndef _CHOOSE_H_
#define _CHOOSE_H_

#include "choice.h"
#include "cad_model.h"

class Choose
{
public:
    Choose();
    ~Choose();
    void select_no_choice();
    void select_choice(Choice c);
    bool marker_visible() const;
    Float3 marker_position() const;
    float marker_angle() const;
    int marker_orientation() const;
    const CadModel& marker_model() const;
    bool new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level);

private:
    CadModel m_marker_model;
    bool m_first_selected;
    bool m_second_selected;
    Choice m_first_choice;
    Choice m_second_choice;
};

#endif // _CHOOSE_H_
