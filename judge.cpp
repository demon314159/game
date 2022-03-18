
#include "judge.h"
#include "element.h"

Judge::Judge()
    : m_min_ix(-1)
    , m_min_face(0)
    , m_min_kind(0)
    , m_min_depth(0.0)
{
}

Judge::~Judge()
{
}

void Judge::add_candidate(int ix, int face, int kind, float depth)
{
    if (m_min_ix == -1) {  // First candidate
        m_min_ix = ix;
        m_min_face = face;
        m_min_kind = kind;
        m_min_depth = depth;
    } else {
        if (depth < m_min_depth) {
            m_min_ix = ix;
            m_min_face = face;
            m_min_kind = kind;
            m_min_depth = depth;
        }
    }
}

int Judge::best_candidate() const
{
    if (m_min_ix == -1)
        return -1;
    if (m_min_face != TOP_FACE)
        return -1;
    return m_min_ix;
}

