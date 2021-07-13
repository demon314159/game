//
// guy.h
//
#if !defined(_GUY_H_)
#define _GUY_H_

#include "sprite.h"

#define GUY_RADIUS 0.25

class Guy: public Sprite
{
    const float run_velocity = 2.0;

public:
    Guy(float left, float right, float back, float front);
    ~Guy();

    void launch(float start_position, float stop_position);
    void relaunch(float move_position);
    bool scored() const;
    void reset_score();

    void update() override;
    bool in_play() const override;
    QVector3D position() const override;
    QVector3D last_position() const override;

protected:
    QVector3D calc_position(float pos) const;

private:
    float m_left;
    float m_right;
    float m_back;
    float m_front;
    float m_start_position;
    float m_stop_position;
    int m_t_launch;
    float m_position; // 0.0 to 4.0
    float m_last_position;
};

#endif // _GUY_H_
