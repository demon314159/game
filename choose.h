
#ifndef _CHOOSE_H_
#define _CHOOSE_H_

#include "float3.h"
#include "cad_model.h"

class Choose
{
public:
    Choose();
    ~Choose();
    void select_no_location();
    void select_location(Float3 pos);
    bool marker1_visible() const;
    bool marker2_visible() const;
    Float3 marker1_position() const;
    Float3 marker2_position() const;
    const CadModel& marker1_model() const;
    const CadModel& marker2_model() const;
    bool new_element_chosen(Float3& pos, int& span, int& orientation);

private:
    CadModel m_marker1_model;
    CadModel m_marker2_model;
    bool m_first_selected;
    bool m_second_selected;
    Float3 m_first_pos;
    Float3 m_second_pos;
};

#endif // _CHOOSE_H_
