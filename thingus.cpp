
#include "thingus.h"
#include <ctype.h>

#include <QVector3D>
#include "paint_can.h"

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
    PaintCan red_paint(1.0, 0.0, 0.0);
    PaintCan blue_paint(0.329412, 0.517647, 1.000000);
    PaintCan pure_green_paint(0.0, 1.0, 0.0);
    PaintCan green_paint(0.329412, 1.0, 0.517647);
    PaintCan gray_paint(0.7, 0.7, 0.7);

    m_cad = new CadModel(StlInterface("board.stl"), green_paint, 0.0);
    CadModel t1(StlInterface("hammer_head.stl"), blue_paint, 1.0);
    t1.add(StlInterface("hammer_bumper.stl"), red_paint, 1.0);
    CadModel t2(StlInterface("hammer_head.stl"), blue_paint, 2.0);
    t2.add(StlInterface("hammer_bumper.stl"), red_paint, 2.0);
    CadModel t3(StlInterface("hammer_head.stl"), blue_paint, 3.0);
    t3.add(StlInterface("hammer_bumper.stl"), red_paint, 3.0);
    CadModel t4(StlInterface("hammer_head.stl"), blue_paint, 4.0);
    t4.add(StlInterface("hammer_bumper.stl"), red_paint, 4.0);
    CadModel t5(StlInterface("hammer_head.stl"), blue_paint, 5.0);
    t5.add(StlInterface("hammer_bumper.stl"), red_paint, 5.0);
    CadModel t6(StlInterface("hammer_head.stl"), blue_paint, 6.0);
    t6.add(StlInterface("hammer_bumper.stl"), red_paint, 6.0);
    CadModel t7(StlInterface("hammer_head.stl"), blue_paint, 7.0);
    t7.add(StlInterface("hammer_bumper.stl"), red_paint, 7.0);
    CadModel bat(StlInterface("bat_sleeve.stl"), red_paint, 8.0);
    bat.add(StlInterface("bat_shaft.stl"), blue_paint, 8.0);
    bat.add(StlInterface("bat_post.stl"), gray_paint, 8.0);
    CadModel pitch(StlInterface("pitch.stl"), pure_green_paint, 9.0);
    CadModel score(StlInterface("score.stl"), blue_paint, 0.0);
    CadModel outs(StlInterface("outs.stl"), blue_paint, 0.0);
    CadModel redx(StlInterface("digit_x.stl"), red_paint, 0.0);
    CadModel right_digit(StlInterface("digit_0.stl"), blue_paint, 40.0);
    right_digit.add(StlInterface("digit_1.stl"), blue_paint, 41.0);
    right_digit.add(StlInterface("digit_2.stl"), blue_paint, 42.0);
    right_digit.add(StlInterface("digit_3.stl"), blue_paint, 43.0);
    right_digit.add(StlInterface("digit_4.stl"), blue_paint, 44.0);
    right_digit.add(StlInterface("digit_5.stl"), blue_paint, 45.0);
    right_digit.add(StlInterface("digit_6.stl"), blue_paint, 46.0);
    right_digit.add(StlInterface("digit_7.stl"), blue_paint, 47.0);
    right_digit.add(StlInterface("digit_8.stl"), blue_paint, 48.0);
    right_digit.add(StlInterface("digit_9.stl"), blue_paint, 49.0);
    CadModel middle_digit(StlInterface("digit_0.stl"), blue_paint, 50.0);
    middle_digit.add(StlInterface("digit_1.stl"), blue_paint, 51.0);
    middle_digit.add(StlInterface("digit_2.stl"), blue_paint, 52.0);
    middle_digit.add(StlInterface("digit_3.stl"), blue_paint, 53.0);
    middle_digit.add(StlInterface("digit_4.stl"), blue_paint, 54.0);
    middle_digit.add(StlInterface("digit_5.stl"), blue_paint, 55.0);
    middle_digit.add(StlInterface("digit_6.stl"), blue_paint, 56.0);
    middle_digit.add(StlInterface("digit_7.stl"), blue_paint, 57.0);
    middle_digit.add(StlInterface("digit_8.stl"), blue_paint, 58.0);
    middle_digit.add(StlInterface("digit_9.stl"), blue_paint, 59.0);
    CadModel left_digit(StlInterface("digit_0.stl"), blue_paint, 60.0);
    left_digit.add(StlInterface("digit_1.stl"), blue_paint, 61.0);
    left_digit.add(StlInterface("digit_2.stl"), blue_paint, 62.0);
    left_digit.add(StlInterface("digit_3.stl"), blue_paint, 63.0);
    left_digit.add(StlInterface("digit_4.stl"), blue_paint, 64.0);
    left_digit.add(StlInterface("digit_5.stl"), blue_paint, 65.0);
    left_digit.add(StlInterface("digit_6.stl"), blue_paint, 66.0);
    left_digit.add(StlInterface("digit_7.stl"), blue_paint, 67.0);
    left_digit.add(StlInterface("digit_8.stl"), blue_paint, 68.0);
    left_digit.add(StlInterface("digit_9.stl"), blue_paint, 69.0);

//    CadModel ball(StlInterface("ball.stl"), gray_paint, 0.0);
    float w = TARGET_WIDTH;
    float h = 0.0;
    m_cad->add(t1, -6.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t2, -4.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t3, -2.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t4, 0.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t5, 2.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t6, 4.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(t7, 6.0 * w, h, TARGET_PIVOT_Z);
    m_cad->add(bat, BAT_PIVOT_X, 0.0, BAT_PIVOT_Z);
    m_cad->add(pitch, 0.0, 0.0, PITCH_PIVOT_Z);
    m_cad->add(score, 2.1, 0.0, 1.9);
    m_cad->add(outs, -2.1, 0.0, 1.9);
    m_cad->add(redx, -2.1, 0.1, 1.9);
    m_cad->add(right_digit, 2.1 + 0.66667, -0.1, 1.9);
    m_cad->add(middle_digit, 2.1, -0.1, 1.9);
    m_cad->add(left_digit, 2.1 - 0.66667, -0.1, 1.9);
//    m_cad->add(ball, 0.0, 0.125, 0.0);
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
