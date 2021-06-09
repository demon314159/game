
#include "thingus.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
};

Thingus::Thingus()
    : m_vertices(0)
    , m_facets(0)
    , indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

  m_flipper = new CadModel("flipper_fillet.wrl");
//    m_flipper = new CadModel("1x1x1_cube.wrl");
//    m_flipper = new CadModel("1x1x1_cube_chamfer.wrl");
//    m_flipper = new CadModel("1x1x1_cube_fillet.wrl");

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

Thingus::~Thingus()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    delete m_flipper;
}

void Thingus::initCubeGeometry()
{
    m_vertices = m_flipper->vertices();
    m_facets = m_flipper->facets();
    if (m_vertices == 0 || m_facets == 0) {
        return;
    }
    VertexData* vertices = new VertexData[m_vertices];
    float x, y, z;
    for (int i = 0; i < m_vertices; i++) {
        m_flipper->get_vertex(i, x, y, z);
        vertices[i].position = QVector3D(x, y, z);
    }
    GLushort* indices = new GLushort[m_facets * 3];
    int a, b, c;
    for (int i = 0; i < m_facets; i++) {
        m_flipper->get_facet(i, a, b, c);
        indices[3 * i] = a;
        indices[3 * i + 1] = b;
        indices[3 * i + 2] = c;
    }

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, m_vertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, m_facets * 3 * sizeof(GLushort));
    delete [] vertices;
    delete [] indices;
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 3 * m_facets, GL_UNSIGNED_SHORT, nullptr);
}
