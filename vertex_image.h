
#ifndef _VERTEX_IMAGE_H_
#define _VERTEX_IMAGE_H_

#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    float animation_id;
};


class VertexImage
{
public:
    VertexImage(int initial_storage);
    ~VertexImage();

    int storage() const;
    void set_storage(int n);

private:
    int m_storage;
};

#endif // _VERTEX_IMAGE_H_
