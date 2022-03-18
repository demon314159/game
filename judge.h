
#ifndef _JUDGE_H_
#define _JUDGE_H

#include "element.h"
#include "mouse_vector.h"

class Judge
{
public:
    Judge();
    ~Judge();
    void add_candidate(int ix, int face, const Element* e, float depth);
    int best_candidate(const MouseVector& mv) const;

private:
    int m_min_ix;
    int m_min_face;
    const Element* m_min_e;
    float m_min_depth;
    int m_best_rejected_roof_top_ix;
    const Element* m_best_rejected_roof_top_e;
    float m_best_rejected_roof_top_depth;

    double len(Float3 v1, Float3 v2) const;
    void add_rejected_roof_top(int ix, const Element* e, float depth);
};

#endif // _JUDGE_H_
