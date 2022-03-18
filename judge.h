
#ifndef _JUDGE_H_
#define _JUDGE_H_

class Judge
{
public:
    Judge();
    ~Judge();
    void add_candidate(int ix, int face, int kind, float depth);
    int best_candidate() const;

private:
    int m_min_ix;
    int m_min_face;
    int m_min_kind;
    float m_min_depth;
};

#endif // _JUDGE_H_
