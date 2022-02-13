
#ifndef _NAVIGATE_H_
#define _NAVIGATE_H_

class Navigate
{
public:
    Navigate();
    ~Navigate();

    void start(int sx, int sy);
    void stop();
    bool active() const;
    bool threshold_exceeded(int sx, int sy, float& degx, float& degy);

private:
    bool m_active;
    int m_sx;
    int m_sy;
};

#endif // _NAVIGATE_H_
