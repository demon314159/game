
#include "thingus.h"

#include <QVector4D>

struct VertexData
{
    QVector4D position;
    QVector4D color;
};

Thingus::Thingus()
    : m_vertices(0)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    vertexBuf.create();

    m_cad = new CadModel("flipper_fillet.wrl");
//    m_cad = new CadModel("1x1x1_cube.wrl");
//    m_cad = new CadModel("1x1x1_cube_chamfer.wrl");
//    m_cad = new CadModel("1x1x1_cube_fillet.wrl");

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

Thingus::~Thingus()
{
    vertexBuf.destroy();
    delete m_cad;
}

void Thingus::initCubeGeometry()
{
    m_vertices = 3 * m_cad->facets();
    if (m_vertices == 0) {
        return;
    }
    VertexData* vertices = new VertexData[m_vertices];
    float3 vp, vc;
    int vix = 0;
    for (int i = 0; i < m_cad->facets(); i++) {
        vc = m_cad->facet_color(i);
        vp = m_cad->facet_v1(i);
        vertices[vix].position = QVector4D(vp.v1, vp.v2, vp.v3, 1.0);
        vertices[vix++].color = QVector4D(vc.v1, vc.v2, vc.v3, 1.0);
        vp = m_cad->facet_v2(i);
        vertices[vix].position = QVector4D(vp.v1, vp.v2, vp.v3, 1.0);
        vertices[vix++].color = QVector4D(vc.v1, vc.v2, vc.v3, 1.0);
        vp = m_cad->facet_v3(i);
        vertices[vix].position = QVector4D(vp.v1, vp.v2, vp.v3, 1.0);
        vertices[vix++].color = QVector4D(vc.v1, vc.v2, vc.v3, 1.0);
    }
    // Transfer vertex data to VBO 0
    vertexBuf.bind();
    vertexBuf.allocate(vertices, m_vertices * sizeof(VertexData));

    delete [] vertices;
}

void Thingus::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    vertexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    // Offset for color coordinate
    offset += sizeof(QVector4D);

    // Tell OpenGL programmable pipeline how to locate color coordinate data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 4, sizeof(VertexData));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices);
}
