//
// sprite.h
//
#if !defined(_SPRITE_H_)
#define _SPRITE_H_

#include <QVector3D>

class Sprite
{
public:
    virtual void update() = 0;
    virtual bool in_play() const = 0;
    virtual QVector3D position() const = 0;
    virtual QVector3D last_position() const = 0;
};

#endif // _SPRITE_H_
