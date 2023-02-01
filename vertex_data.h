
#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    float animation_id;
};

#endif // _VERTEX_DATA_H_
