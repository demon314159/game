//
// scene.h
//
#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <QPainter>

#define HORZ_UNITS 32
#define VERT_UNITS 24

class Scene
{
public:
    Scene();
    ~Scene();
    void draw(QPainter& painter);

protected:
    int m_xbase;
    int m_ybase;
    int m_unit;

    void determine_size(QPainter& painter);
};

#endif // _SCENE_H_
