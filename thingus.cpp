
#include "thingus.h"
#include <ctype.h>

#include <QVector3D>
#include "paint_can.h"
#include "cube_shape.h"
#include "brick_shape.h"
#include "window_model.h"
#include "bounding_box.h"

#include "elements.h"
#include "document.h"

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    float animation_id;
};

Thingus::Thingus()
    : m_vertices(0)
{
    initializeOpenGLFunctions();
    vertexBuf.create();

    QString file_name = "house.txt";
    Document doc;
    if (!doc.load_from_file(file_name)) {
        printf("Error loading doc: '%s'\n", doc.error_message().toLatin1().data());
    } else {
        printf("Loaded doc\n");
    }
    CadModel house;
    doc.build_model(&house);
    printf("house has %d facets\n", house.facets());

// this step should be removed so there is just one model built, the view should handle this job
    m_cad = new CadModel(house, -2.0, -2.0, 0.0);
    BoundingBox bb = m_cad->bounding_box();
    float tablex = bb.vmax.v1 - bb.vmin.v1 + 2 * Element::dimw;
    float tabley = Element::dimh / 20.0;
    float tablez = bb.vmax.v3 - bb.vmin.v3 + 2 * Element::dimw;

//    PaintCan table_paint(0.658, 1.0, 1.0);
    PaintCan table_paint(0.4, 0.8, 1.0);

    CubeShape table(tablex, tabley, tablez);
    CadModel tt(table, table_paint, 1.0);
    m_cad->add(tt, bb.vmin.v1 + tablex / 2.0 - Element::dimw, bb.vmin.v2, bb.vmin.v3 + tablez / 2 - Element::dimw);
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
    float an_id;
    float3 vp, vc, vn;
    int vix = 0;
    for (int i = 0; i < m_cad->facets(); i++) {
        an_id = m_cad->facet_animation_id(i);
        vc = m_cad->facet_color(i);
        vn = m_cad->facet_normal(i);
        vp = m_cad->facet_v1(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = m_cad->facet_v2(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = m_cad->facet_v3(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
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
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for normal
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate normal data
    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for color coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate color coordinate data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for animation_id
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate animation_id
    int animationIdLocation = program->attributeLocation("a_animation_id");
    program->enableAttributeArray(animationIdLocation);
    program->setAttributeBuffer(animationIdLocation, GL_FLOAT, offset, 1, sizeof(VertexData));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices);
}
