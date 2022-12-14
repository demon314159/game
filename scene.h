//
// scene.h
//
#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <QPainter>

class Scene
{
public:
    Scene();
    ~Scene();
    void draw(QPainter& painter, int x_base, int y_base, int width, int height);

protected:
};

#endif // _SCENE_H_
