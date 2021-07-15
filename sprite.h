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
    Sprite(const QString& file_name, float radius, const QVector3D& error_vector);
    float radius() const;
    QVector3D error_vector() const;
    QImage copy(int x, int y, int w, int h) const;
    virtual bool is_reversed() const;
    virtual void update() = 0;
    virtual bool in_play() const = 0;
    virtual QVector3D position() const = 0;
    virtual QVector3D last_position() const = 0;
private:
    float m_radius;
    QVector3D m_error_vector;
    QImage m_set;
};

#endif // _SPRITE_H_
