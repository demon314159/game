
#include "judge.h"
#include <math.h>

Judge::Judge()
    : m_min_ix(-1)
    , m_min_face(0)
    , m_min_e(NULL)
    , m_min_depth(0.0)
    , m_best_rejected_roof_top_ix(-1)
    , m_best_rejected_roof_top_e(NULL)
    , m_best_rejected_roof_top_depth(0.0)
{
}

Judge::~Judge()
{
}

void Judge::add_candidate(int ix, int face, const Element* e, float depth)
{
    if (m_min_ix == -1) {  // First candidate
        m_min_ix = ix;
        m_min_face = face;
        m_min_e = e;
        m_min_depth = depth;
    } else {
        if (depth < m_min_depth) { // Accept new element as best
            if (m_min_e->kind() == ELEMENT_ROOF && m_min_face == TOP_FACE) {
                add_rejected_roof_top(m_min_ix, m_min_e, m_min_depth);
            }
            m_min_ix = ix;
            m_min_face = face;
            m_min_e = e;
            m_min_depth = depth;
        } else { // Reject new element
            if (e->kind() == ELEMENT_ROOF && face == TOP_FACE) {
                add_rejected_roof_top(ix, e, depth);
            }
        }
    }
}

void Judge::add_rejected_roof_top(int ix, const Element* e, float depth)
{
    if (m_best_rejected_roof_top_ix == -1) { // First rejected roof topi
        m_best_rejected_roof_top_ix = ix;
        m_best_rejected_roof_top_e = e;
        m_best_rejected_roof_top_depth = depth;
    } else {
        if (depth < m_best_rejected_roof_top_depth) { // Accept new reject as best
            m_best_rejected_roof_top_ix = ix;
            m_best_rejected_roof_top_e = e;
            m_best_rejected_roof_top_depth = depth;
        }
    }
}

int Judge::best_candidate(const MouseVector& mv) const
{
    if (m_min_ix == -1)
        return -1;
    if (m_min_face != TOP_FACE)
        return -1;
    if (m_min_e->kind() == ELEMENT_ROOF && m_best_rejected_roof_top_ix != -1) {
        if (fabs(m_best_rejected_roof_top_depth - m_min_depth) < 0.0001) {
            Float3 ip = mv.intersection_point(m_min_depth);
            float len1 = len(ip, m_min_e->pos());
            float len2 = len(ip, m_best_rejected_roof_top_e->pos());
            if (len2 < len1) {
                return m_best_rejected_roof_top_ix;
            }
        }
    }
    return m_min_ix;
}

double Judge::len(Float3 v1, Float3 v2) const
{
    double a = v1.v1 - v2.v1;
    double b = v1.v2 - v2.v2;
    double c = v1.v3 - v2.v3;
    return sqrt(a * a + b * b + c * c);
}

