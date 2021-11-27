
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
    bool marker_visible() const;
    Float3 marker_position() const;
    const CadModel& marker_model() const;

private:
    CadModel m_marker_model;
    bool m_first_selected;
    bool m_second_selected;
    Float3 m_first_pos;
    Float3 m_second_pos;
};

#endif // _CHOOSE_H_
