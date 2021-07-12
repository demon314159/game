//
// ball.h
//
#if !defined(_BALL_H_)
#define _BALL_H_

#include "sprite.h"

#define BALL_RADIUS 0.125

class Ball: public Sprite
{
    const float launch_velocity = 6.0;
    const float hit_velocity = launch_velocity * 4.0;
public:
    Ball(float back_width, float front_width, float back, float front);
    ~Ball();

    void launch(const QVector3D& launch_position);
    void hit(const QVector3D& bat_pivot_position);
    void stop();
    void reset();
    bool stopped() const;
    void update() override;
    bool in_play() const override;
    QVector3D position() const override;
    QVector3D last_position() const override;

protected:
    QVector3D position_now(int t_now);
    bool reflect(QVector3D& pos);
    void check_limits(QVector3D& pos);
    float left_border(float z) const;
    float right_border(float z) const;

private:
    float m_back_width;
    float m_front_width;
    float m_back;
    float m_front;
    int m_t_launch;
    int m_t_hit;
    QVector3D m_velocity;
    bool m_stopped;
    QVector3D m_launch_position;
    QVector3D m_hit_position;
    QVector3D m_position;
    QVector3D m_last_position;
};

#endif // _BALL_H_
