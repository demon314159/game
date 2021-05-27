
#include "thingus.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

Thingus::Thingus()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

Thingus::~Thingus()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Thingus::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        {QVector3D(0.0f, 0.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(-1.0f, 1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, // v1
        {QVector3D( 1.0f, 1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v2
        {QVector3D(-1.0f,-1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, // v3
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, // v4
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,
         0, 3, 4
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
//    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));
    arrayBuf.allocate(vertices, 5 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
//    indexBuf.allocate(indices, 34 * sizeof(GLushort));
    indexBuf.allocate(indices, 6 * sizeof(GLushort));
}

void Thingus::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}
