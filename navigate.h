
#ifndef _NAVIGATE_H_
#define _NAVIGATE_H_

class Navigate
{
public:
    Navigate();
    ~Navigate();

    void start_rotate(int sx, int sy);
    void start_translate(int sx, int sy);
    void stop();
    bool active() const;
    bool is_rotate() const;
    bool is_translate() const;
    bool rotate_threshold_exceeded(int sx, int sy, float& degx, float& degy);
    bool translate_threshold_exceeded(int sx, int sy, int& dx, int& dy);

private:
    bool m_rotate;
    bool m_translate;
    int m_sx;
    int m_sy;
};

#endif // _NAVIGATE_H_
