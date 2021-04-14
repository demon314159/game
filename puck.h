//
// puck.h
//
#if !defined(_PUCK_H_)
#define _PUCK_H_

class Puck
{
public:
    Puck(double velocity_x, double velocity_y);

protected:
    double velocity_x() const;
    double velocity_y() const;

private:
    int m_velocity_x;
    int m_velocity_y;
};

#endif // _PUCK_H_
