
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
    VertexImage(int initial_max_vertex_count);
    ~VertexImage();

    int max_vertex_count() const;
    void set_max_vertex_count(int n);

private:
    int m_max_vertex_count;
    int m_vertex_count;
    VertexData* m_vertex_data;
};

#endif // _VERTEX_IMAGE_H_
