
#include "mouse_vector.h"
#include "math.h"

MouseVector::MouseVector(Float3 origin, Float3 vector)
    : m_origin(origin)
    , m_vector(vector)
{
}

MouseVector::~MouseVector()
{
}

Float3 MouseVector::origin() const
{
    return m_origin;
}

Float3 MouseVector::vector() const
{
    return m_vector;
}

void MouseVector::set_new_vector(Float3 origin, Float3 vector)
{
    m_origin = origin;
    m_vector = vector;
}

void MouseVector::translate(Float3 off)
{
    m_origin.v1 += off.v1;
    m_origin.v2 += off.v2;
    m_origin.v3 += off.v3;
}

void MouseVector::rotate_ay(float deg)
{
    double angle = deg * 3.1415926536 / 180.0;
    Float3 t_org = m_origin;
    Float3 t_vec = m_vector;
    t_org.v1 = m_origin.v1 * cos(angle) - m_origin.v3 * sin(angle);
    t_org.v3 = m_origin.v1 * sin(angle) + m_origin.v3 * cos(angle);
    t_vec.v1 = m_vector.v1 * cos(angle) - m_vector.v3 * sin(angle);
    t_vec.v3 = m_vector.v1 * sin(angle) + m_vector.v3 * cos(angle);
    m_origin = t_org;
    m_vector = t_vec;
}

void MouseVector::rotate_ax(float deg)
{
    double angle = deg * 3.1415926536 / 180.0;
    Float3 t_org = m_origin;
    Float3 t_vec = m_vector;
    t_org.v2 = m_origin.v2 * cos(angle) + m_origin.v3 * sin(angle);
    t_org.v3 = -m_origin.v2 * sin(angle) + m_origin.v3 * cos(angle);
    t_vec.v2 = m_vector.v2 * cos(angle) + m_vector.v3 * sin(angle);
    t_vec.v3 = -m_vector.v2 * sin(angle) + m_vector.v3 * cos(angle);
    m_origin = t_org;
    m_vector = t_vec;
}


