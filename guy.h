//
// guy.h
//
#if !defined(_GUY_H_)
#define _GUY_H_

#include <QVector3D>

#define GUY_RADIUS 0.25

class Guy
{
    const float run_velocity = 4.4;
public:
    Guy(float left, float right, float back, float front);
    ~Guy();

    void launch(float start_position, float stop_position);
    void update();
    QVector3D calc_position(float pos) const;
    QVector3D position() const;
    QVector3D last_position() const;

    bool in_play() const;

protected:

private:
    float m_left;
    float m_right;
    float m_back;
    float m_front;
    float m_stop_position;
    int m_t_launch;
    float m_position; // 0.0 to 4.0
    float m_last_position;
};

#endif // _GUY_H_
