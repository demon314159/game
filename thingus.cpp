
#include "thingus.h"
#include <ctype.h>

#include <QVector3D>
#include "paint_can.h"
#include "brick_shape.h"

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
    PaintCan lit_paint(2.0, 2.0, 0.0);
    float f = 0.6;
    PaintCan unlit_paint(f, f, 0.0);
    PaintCan white_paint(1.0, 1.0, 1.0);
    PaintCan black_paint(0.0, 0.0, 0.0);
    PaintCan red_paint(1.0, 0.0, 0.0);
    PaintCan blue_paint(0.329412, 0.517647, 1.000000);
    PaintCan brown_paint(0.71, 0.396, 0.114);
    PaintCan pure_green_paint(0.0, 1.0, 0.0);
    PaintCan green_paint(0.329412, 1.0, 0.517647);
    PaintCan table_paint(0.658, 1.0, 1.0);
    PaintCan gray_paint(0.7, 0.7, 0.7);

    float dimw = 1.0;
    float dimh = 2.0 / 3.0;
    float dimb = 0.025;

    float tablex = 9.0 * dimw;
    float tabley = dimh / 20.0;
    float tablez = 7.0 * dimw;
    float tableb = dimb / 20.0;

    BrickShape front_brick(2.0 * dimw, dimh, dimw, dimb);
    BrickShape side_brick(dimw, dimh, 2.0 * dimw, dimb);
    BrickShape half_brick(dimw, dimh, dimw, dimb);
    BrickShape table(tablex, tabley, tablez, tableb);

    CadModel tf = CadModel(front_brick, red_paint, 0.0);
    CadModel ts = CadModel(side_brick, red_paint, 0.0);
    CadModel th = CadModel(half_brick, red_paint, 0.0);
    CadModel tt = CadModel(table, table_paint, 1.0);
    float y_offset = -2.0;
    float h = y_offset;
    m_cad = new CadModel();


    BrickShape vslat(0.2 * dimw, 4 * dimw, 0.2 *dimw, dimb);
    CadModel vs = CadModel(vslat, white_paint, 0.0);
    BrickShape hslat(3.0 * dimw, 0.2 * dimw, 0.2 * dimw, dimb);
    CadModel hs = CadModel(hslat, white_paint, 0.0);

    float ground = y_offset - dimh / 2.0;
    float wz = dimw / 2.0 - 0.1 * dimw;
    m_cad->add(vs, (0.0 + 0.1) * dimw, ground + 2 * dimw + 2.0 * dimh, wz);
    m_cad->add(vs, (1.0) * dimw, ground + 2 * dimw + 2.0 * dimh, wz);
    m_cad->add(vs, (2.0) * dimw, ground + 2 * dimw + 2.0 * dimh, wz);
    m_cad->add(vs, (3.0 - 0.1) * dimw, ground + 2 * dimw + 2.0 * dimh, wz);
    m_cad->add(hs, 1.5 * dimw, ground + (0.0 + 0.1) * dimw + 2.0 * dimh, wz);
    m_cad->add(hs, 1.5 * dimw, ground + (1.0) * dimw + 2.0 * dimh, wz);
    m_cad->add(hs, 1.5 * dimw, ground + (2.0) * dimw + 2.0 * dimh, wz);
    m_cad->add(hs, 1.5 * dimw, ground + (3.0) * dimw + 2.0 * dimh, wz);
    m_cad->add(hs, 1.5 * dimw, ground + (4.0 - 0.1) * dimw + 2.0 * dimh, wz);

    m_cad->add(th, -1.5, h, -4.0);
    m_cad->add(ts, -1.5, h, -2.5);
    m_cad->add(ts, -1.5, h, -0.5);
    m_cad->add(tf, 0.0, h, 0.0);
    m_cad->add(tf, 2.0, h, 0.0);
    m_cad->add(tf, 4.0, h, 0.0);

    h = y_offset + 2.0 / 3.0;
    m_cad->add(ts, -1.5, h, -3.5);
    m_cad->add(ts, -1.5, h, -1.5);
    m_cad->add(tf, -1.0, h, 0.0);
    m_cad->add(tf, 1.0, h, 0.0);
    m_cad->add(tf, 3.0, h, 0.0);
    m_cad->add(th, 4.5, h, 0.0);

    h = y_offset + 4.0 / 3.0;
    m_cad->add(th, -1.5, h, -4.0);
    m_cad->add(ts, -1.5, h, -2.5);
    m_cad->add(ts, -1.5, h, -0.5);
    m_cad->add(th, -0.5, h, 0.0);
    m_cad->add(tf, 4.0, h, 0.0);

    h = y_offset + 6.0 / 3.0;
    m_cad->add(ts, -1.5, h, -3.5);
    m_cad->add(ts, -1.5, h, -1.5);
    m_cad->add(tf, -1.0, h, 0.0);
    m_cad->add(th, 3.5, h, 0.0);
    m_cad->add(th, 4.5, h, 0.0);

    h = y_offset + 8.0 / 3.0;
    m_cad->add(th, -1.5, h, -4.0);
    m_cad->add(ts, -1.5, h, -2.5);
    m_cad->add(ts, -1.5, h, -0.5);
    m_cad->add(th, -0.5, h, 0.0);
    m_cad->add(tf, 4.0, h, 0.0);
    m_cad->add(tt, tablex / 2.0 - 3.0, y_offset - dimh / 2.0 - tabley / 2.0, 1.5 - tablez / 2.0);

    h = y_offset + 10.0 / 3.0;
    m_cad->add(ts, -1.5, h, -3.5);
    m_cad->add(ts, -1.5, h, -1.5);
    m_cad->add(tf, -1.0, h, 0.0);
    m_cad->add(th, 3.5, h, 0.0);
    m_cad->add(th, 4.5, h, 0.0);

    h = y_offset + 12.0 / 3.0;
    m_cad->add(th, -1.5, h, -4.0);
    m_cad->add(ts, -1.5, h, -2.5);
    m_cad->add(ts, -1.5, h, -0.5);
    m_cad->add(th, -0.5, h, 0.0);
    m_cad->add(tf, 4.0, h, 0.0);
    m_cad->add(tt, tablex / 2.0 - 3.0, y_offset - dimh / 2.0 - tabley / 2.0, 1.5 - tablez / 2.0);

    h = y_offset + 14.0 / 3.0;
    m_cad->add(ts, -1.5, h, -3.5);
    m_cad->add(ts, -1.5, h, -1.5);
    m_cad->add(tf, -1.0, h, 0.0);
    m_cad->add(th, 3.5, h, 0.0);
    m_cad->add(th, 4.5, h, 0.0);

    h = y_offset + 16.0 / 3.0;
    m_cad->add(th, -1.5, h, -4.0);
    m_cad->add(ts, -1.5, h, -2.5);
    m_cad->add(ts, -1.5, h, -0.5);
    m_cad->add(tf, 0.0, h, 0.0);
    m_cad->add(tf, 2.0, h, 0.0);
    m_cad->add(tf, 4.0, h, 0.0);

    m_cad->add(tt, tablex / 2.0 - 3.0, y_offset - dimh / 2.0 - tabley / 2.0, 1.5 - tablez / 2.0);

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
