//
// sprite.h
//
#if !defined(_SPRITE_H_)
#define _SPRITE_H_

#include <QImage>
#include <QVector3D>

class Sprite
{
public:
    Sprite(const QString& file_name, float radius);
    float radius() const;
    QImage copy(int x, int y, int w, int h) const;
    virtual void update() = 0;
    virtual bool in_play() const = 0;
    virtual QVector3D position() const = 0;
    virtual QVector3D last_position() const = 0;
private:
    float m_radius;
    QImage m_set;
};

#endif // _SPRITE_H_
