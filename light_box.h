//
// light_box.h
//
#if !defined(_LIGHT_BOX_H_)
#define _LIGHT_BOX_H_

class LightBox
{
    static const int LIGHTS = 7;
public:
    LightBox();
    ~LightBox();

    int lights() const;
    bool is_on(int ix) const;
    bool all_on() const;
    void set_on(int ix);
    void set_all_off();

protected:

private:
    bool m_on_flag[LIGHTS];
};

#endif // _LIGHT_BOX_H_
