//
// ball.h
//
#if !defined(_BALL_H_)
#define _BALL_H_

#include <QVector3D>

class Ball
{
    const float velocity = 6.0;
    const float hit_velocity = velocity * 4.0;
public:
    Ball();
    ~Ball();

    void launch(const QVector3D& launch_position);
    void hit(const QVector3D& bat_pivot_position);
    void stop();
    void update();

    bool in_play() const;
    QVector3D position() const;
    QVector3D last_position() const;

protected:
    QVector3D position_now(int t_now) const;

private:
    int m_t_launch;
    int m_t_hit;
    QVector3D m_launch_position;
    QVector3D m_bat_pivot_position;
    QVector3D m_position;
    QVector3D m_last_position;
};

#endif // _BALL_H_
