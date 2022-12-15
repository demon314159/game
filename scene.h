//
// scene.h
//
#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <QPainter>
#include "shape_set.h"

#define HORZ_UNITS 24
#define VERT_UNITS 18

class Scene
{
public:
    Scene(const ShapeSet* shape_set);
    ~Scene();
    void draw(QPainter& painter);
    void next_shape();
    void prev_shape();

protected:
    const ShapeSet* m_shape_set;
    int m_current_shape;
    int m_xbase;
    int m_ybase;
    int m_unit;

    void determine_layout(QPainter& painter);
    QRect dock(int dix) const;

    void draw_shape(QPainter& painter, const QRect& rect, int shape_id, int orientation);
};

#endif // _SCENE_H_
