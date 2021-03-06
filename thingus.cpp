
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

Thingus::Thingus(float tilt)
    : m_tilt(tilt)
    , m_vertices(0)
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
    PaintCan gray_paint(0.7, 0.7, 0.7);

    m_cad = new CadModel(StlInterface(":/board.stl"), green_paint, 0.0);
    CadModel t1(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET1);
    t1.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET1);
    t1.add(StlInterface(":/t_single.stl"), white_paint, ANI_ID_TARGET1);
    t1.rotate_ax(90.0 - m_tilt);
    CadModel t2(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET2);
    t2.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET2);
    t2.add(StlInterface(":/t_triple.stl"), white_paint, ANI_ID_TARGET2);
    t2.rotate_ax(90.0 - m_tilt);
    CadModel t3(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET3);
    t3.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET3);
    t3.add(StlInterface(":/t_double.stl"), white_paint, ANI_ID_TARGET3);
    t3.rotate_ax(90.0 - m_tilt);
    CadModel t4(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET4);
    t4.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET4);
    t4.add(StlInterface(":/t_homer.stl"), white_paint, ANI_ID_TARGET4);
    t4.rotate_ax(90.0 - m_tilt);
    CadModel t5(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET5);
    t5.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET5);
    t5.add(StlInterface(":/t_double.stl"), white_paint, ANI_ID_TARGET5);
    t5.rotate_ax(90.0 - m_tilt);
    CadModel t6(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET6);
    t6.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET6);
    t6.add(StlInterface(":/t_triple.stl"), white_paint, ANI_ID_TARGET6);
    t6.rotate_ax(90.0 - m_tilt);
    CadModel t7(StlInterface(":/target_body.stl"), blue_paint, ANI_ID_TARGET7);
    t7.add(StlInterface(":/target_bumper.stl"), red_paint, ANI_ID_TARGET7);
    t7.add(StlInterface(":/t_single.stl"), white_paint, ANI_ID_TARGET7);
    t7.rotate_ax(90.0 - m_tilt);
    CadModel bat(StlInterface(":/bat_sleeve.stl"), red_paint, ANI_ID_BAT);
    bat.add(StlInterface(":/bat_shaft.stl"), blue_paint, ANI_ID_BAT);
    bat.add(StlInterface(":/bat_post.stl"), gray_paint, ANI_ID_BAT);
    CadModel pitch(StlInterface(":/pitch.stl"), pure_green_paint, ANI_ID_PITCH);
    CadModel score(StlInterface(":/score.stl"), blue_paint, 0.0);
    CadModel outs(StlInterface(":/outs.stl"), blue_paint, 0.0);
    CadModel right_digit(StlInterface(":/digit_0.stl"), blue_paint, ANI_ID_SCORE_RIGHT);
    right_digit.add(StlInterface(":/digit_1.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 1.0);
    right_digit.add(StlInterface(":/digit_2.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 2.0);
    right_digit.add(StlInterface(":/digit_3.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 3.0);
    right_digit.add(StlInterface(":/digit_4.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 4.0);
    right_digit.add(StlInterface(":/digit_5.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 5.0);
    right_digit.add(StlInterface(":/digit_6.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 6.0);
    right_digit.add(StlInterface(":/digit_7.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 7.0);
    right_digit.add(StlInterface(":/digit_8.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 8.0);
    right_digit.add(StlInterface(":/digit_9.stl"), blue_paint, ANI_ID_SCORE_RIGHT + 9.0);
    CadModel middle_digit(StlInterface(":/digit_0.stl"), blue_paint, ANI_ID_SCORE_MIDDLE);
    middle_digit.add(StlInterface(":/digit_1.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 1.0);
    middle_digit.add(StlInterface(":/digit_2.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 2.0);
    middle_digit.add(StlInterface(":/digit_3.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 3.0);
    middle_digit.add(StlInterface(":/digit_4.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 4.0);
    middle_digit.add(StlInterface(":/digit_5.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 5.0);
    middle_digit.add(StlInterface(":/digit_6.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 6.0);
    middle_digit.add(StlInterface(":/digit_7.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 7.0);
    middle_digit.add(StlInterface(":/digit_8.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 8.0);
    middle_digit.add(StlInterface(":/digit_9.stl"), blue_paint, ANI_ID_SCORE_MIDDLE + 9.0);
    CadModel left_digit(StlInterface(":/digit_0.stl"), blue_paint, ANI_ID_SCORE_LEFT);
    left_digit.add(StlInterface(":/digit_1.stl"), blue_paint, ANI_ID_SCORE_LEFT + 1.0);
    left_digit.add(StlInterface(":/digit_2.stl"), blue_paint, ANI_ID_SCORE_LEFT + 2.0);
    left_digit.add(StlInterface(":/digit_3.stl"), blue_paint, ANI_ID_SCORE_LEFT + 3.0);
    left_digit.add(StlInterface(":/digit_4.stl"), blue_paint, ANI_ID_SCORE_LEFT + 4.0);
    left_digit.add(StlInterface(":/digit_5.stl"), blue_paint, ANI_ID_SCORE_LEFT + 5.0);
    left_digit.add(StlInterface(":/digit_6.stl"), blue_paint, ANI_ID_SCORE_LEFT + 6.0);
    left_digit.add(StlInterface(":/digit_7.stl"), blue_paint, ANI_ID_SCORE_LEFT + 7.0);
    left_digit.add(StlInterface(":/digit_8.stl"), blue_paint, ANI_ID_SCORE_LEFT + 8.0);
    left_digit.add(StlInterface(":/digit_9.stl"), blue_paint, ANI_ID_SCORE_LEFT + 9.0);
    CadModel left_out(StlInterface(":/digit_x.stl"), red_paint, ANI_ID_OUT1);
    CadModel middle_out(StlInterface(":/digit_x.stl"), red_paint, ANI_ID_OUT2);
    CadModel right_out(StlInterface(":/digit_x.stl"), red_paint, ANI_ID_OUT3);
    right_out.add(StlInterface(":/game_over.stl"), red_paint, ANI_ID_OUT3);
    CadModel diamond(StlInterface(":/diamond.stl"), brown_paint, 0.0);
    CadModel bases(StlInterface(":/bases.stl"), white_paint, 0.0);
    CadModel side_bumpers(StlInterface(":/side_bumpers.stl"), red_paint, 0.0);
    CadModel unlit_light(StlInterface(":/light_base.stl"), black_paint, 0.0);
    unlit_light.add(StlInterface(":/light_top.stl"), unlit_paint, 0.0);
    CadModel lit_light1(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT1);
    CadModel lit_light2(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT2);
    CadModel lit_light3(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT3);
    CadModel lit_light4(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT4);
    CadModel lit_light5(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT5);
    CadModel lit_light6(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT6);
    CadModel lit_light7(StlInterface(":/light_top.stl"), lit_paint, ANI_ID_LIGHT7);
    CadModel cancel(StlInterface(":/cancel.stl"), blue_paint, 0.0);

    float w = TARGET_WIDTH;
    float h = TARGET_PIVOT_Y;
    float ll = -7.0;
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
    m_cad->add(right_digit, 2.1 + 0.66667, -0.1, 1.9);
    m_cad->add(middle_digit, 2.1, -0.1, 1.9);
    m_cad->add(left_digit, 2.1 - 0.66667, -0.1, 1.9);
    m_cad->add(left_out, -2.1 - 0.66667, -1.0/50.0 -0.1, 1.9);
    m_cad->add(middle_out, -2.1, -1.0/50.0 -0.1, 1.9);
    m_cad->add(right_out, -2.1 + 0.66667, -1.0/50.0 -0.1, 1.9);
    m_cad->add(diamond, 0.0, 0.0, 0.0);
    m_cad->add(bases, 0.0, 0.0, 0.0);
    m_cad->add(side_bumpers, 0.0, 0.0, 0.0);
    float thickness = 0.05;
    float rise = thickness / 8.0;
    m_cad->add(unlit_light, -6.0 * w, 0.0, ll);
    m_cad->add(unlit_light, -4.0 * w, 0.0, ll);
    m_cad->add(unlit_light, -2.0 * w, 0.0, ll);
    m_cad->add(unlit_light, 0.0, 0.0, ll);
    m_cad->add(unlit_light, 2.0 * w, 0.0, ll);
    m_cad->add(unlit_light, 4.0 * w, 0.0, ll);
    m_cad->add(unlit_light, 6.0 * w, 0.0, ll);
    m_cad->add(lit_light1, -6.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light2, -4.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light3, -2.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light4, 0.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light5, 2.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light6, 4.0 * w, rise - 0.1, ll);
    m_cad->add(lit_light7, 6.0 * w, rise - 0.1, ll);
    m_cad->add(cancel, 0.0, 0.0, 0.0);
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
