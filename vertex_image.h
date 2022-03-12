
#ifndef _VERTEX_IMAGE_H_
#define _VERTEX_IMAGE_H_

#include "element.h"
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
    static const int INITIAL_MAX_VERTEX_COUNT = 1024 * 1024;
    VertexImage();
    ~VertexImage();
    int vertex_count() const;
    void add_element(Element* e, bool transparent);
    void update_element(int start_ix, const Element*e, bool transparent);
    const VertexData* vertex_data() const;
    void trim_to(int vix);

private:
    int m_max_vertex_count;
    int m_vertex_count;
    VertexData* m_vertex_data;

    void double_the_storage();
    void add_vertex(VertexData& vd);
};

#endif // _VERTEX_IMAGE_H_
