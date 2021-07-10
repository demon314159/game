//
// guy.h
//
#if !defined(_GUY_H_)
#define _GUY_H_

#include <QVector3D>

class Guy
{
    const float run_velocity = 4.4;
public:
    Guy(float left, float right, float back, float front);
    ~Guy();

    QVector3D position(int base) const;

protected:

private:
    float m_left;
    float m_right;
    float m_back;
    float m_front;
};

#endif // _GUY_H_
