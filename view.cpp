#include "view.h"
#include "paint_can.h"
#include "cube_shape.h"
#include "brick_shape.h"
#include "curve_shape.h"
#include "ring_shape.h"
#include "cylinder_shape.h"
#include "straight_track_shape.h"
#include "curved_track_shape.h"
#include "bounding_box.h"
#include "look.h"
#include "track_style.h"
#include <math.h>
#include <stdio.h>

#define notVERBOSE

View::View()
    : m_max_vertex_count(1024 * 1024)
    , m_aux_count(0)
    , m_table(new CadModel())
    , m_aux_model(new CadModel())
    , m_change(true)
    , m_radius(2.0)
    , m_center({0.0, 0.0, 0.0})
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_aspect(1.0)
    , m_mag(1.0)
    , m_fov(45.0)
    , m_camz(8.0)
    , m_xrot(0.0)
    , m_yrot(0.0)
    , m_xoff(0.0)
    , m_yoff(0.0)
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
//    build_wheels(TrackStyle::car_width);
//    build_track();
    build_car();
    decorate_model();
    m_aux_model->add(*m_table);
    m_change = false;
}


Curve View::front_curve() const
{
    int np = 4;
    Matrix given(np, 2);
    given.set(0, 0, 0.0); given.set(0, 1, 5.0);
    given.set(1, 0, 10.0); given.set(1, 1, 4.0);
    given.set(2, 0, 9.0); given.set(2, 1, 0.5);
    given.set(3, 0, 0.0); given.set(3, 1, 0.0);
    int top_steps = 9;
    int bottom_steps = 9;
    int side_steps = 9;
    int fillet_steps = 9;
    double top_shrink = 0.05;
    double bottom_shrink = 0.05;
    double side_top_shrink = 0.2;
    double side_bottom_shrink = 0.2;
    Double2 p1 = {-given.get(1, 0), given.get(1, 1)};
    Double2 p2 = {given.get(0, 0), given.get(0, 1)};
    Double2 p3 = {given.get(1, 0), given.get(1, 1)};
    Radial top_rad(p1, p2, p3, top_steps);
    p1 = {given.get(2, 0), given.get(2, 1)};
    p2 = {given.get(3, 0), given.get(3, 1)};
    p3 = {-given.get(2, 0), given.get(2, 1)};
    Radial bottom_rad(p1, p2, p3, bottom_steps);
    p1 = {given.get(1, 0), given.get(1, 1)};
    p2 = {given.get(2, 0), given.get(2, 1)};
    Radial right_rad(p1, p2, 10.0, side_steps);
    p2 = {-given.get(1, 0), given.get(1, 1)};
    p1 = {-given.get(2, 0), given.get(2, 1)};
    Radial left_rad(p1, p2, 10.0, side_steps);
    top_rad = top_rad.shrunk(top_shrink, 1.0 - top_shrink);
    bottom_rad = bottom_rad.shrunk(bottom_shrink, 1.0 - bottom_shrink);
    right_rad = right_rad.shrunk(side_top_shrink, 1.0 - side_bottom_shrink);
    left_rad = left_rad.shrunk(side_bottom_shrink, 1.0 - side_top_shrink);
    Radial top_right_rad(top_rad, right_rad, fillet_steps);
    Radial top_left_rad(left_rad, top_rad, fillet_steps);
    Radial bottom_right_rad(right_rad, bottom_rad, fillet_steps);
    Radial bottom_left_rad(bottom_rad, left_rad, fillet_steps);
    Curve curve;
    curve.add(bottom_left_rad);
    curve.add(left_rad);
    curve.add(top_left_rad);
    curve.add(top_rad);
    curve.add(top_right_rad);
    curve.add(right_rad);
    curve.add(bottom_right_rad);
    curve.add(bottom_rad);
    return curve;
}

Curve View::back_curve() const
{
    int np = 4;
    Matrix given(np, 2);
    given.set(0, 0, 0.0); given.set(0, 1, 10.0);
    given.set(1, 0, 13.0); given.set(1, 1, 8.0);
    given.set(2, 0, 12.0); given.set(2, 1, 0.0);
    given.set(3, 0, 0.0); given.set(3, 1, -1.0);
    int top_steps = 9;
    int bottom_steps = 9;
    int side_steps = 9;
    int fillet_steps = 9;
    double top_shrink = 0.05;
    double bottom_shrink = 0.05;
    double side_top_shrink = 0.2;
    double side_bottom_shrink = 0.2;
    Double2 p1 = {-given.get(1, 0), given.get(1, 1)};
    Double2 p2 = {given.get(0, 0), given.get(0, 1)};
    Double2 p3 = {given.get(1, 0), given.get(1, 1)};
    Radial top_rad(p1, p2, p3, top_steps);
    p1 = {given.get(2, 0), given.get(2, 1)};
    p2 = {given.get(3, 0), given.get(3, 1)};
    p3 = {-given.get(2, 0), given.get(2, 1)};
    Radial bottom_rad(p1, p2, p3, bottom_steps);
    p1 = {given.get(1, 0), given.get(1, 1)};
    p2 = {given.get(2, 0), given.get(2, 1)};
    Radial right_rad(p1, p2, 10.0, side_steps);
    p2 = {-given.get(1, 0), given.get(1, 1)};
    p1 = {-given.get(2, 0), given.get(2, 1)};
    Radial left_rad(p1, p2, 10.0, side_steps);
    top_rad = top_rad.shrunk(top_shrink, 1.0 - top_shrink);
    bottom_rad = bottom_rad.shrunk(bottom_shrink, 1.0 - bottom_shrink);
    right_rad = right_rad.shrunk(side_top_shrink, 1.0 - side_bottom_shrink);
    left_rad = left_rad.shrunk(side_bottom_shrink, 1.0 - side_top_shrink);
    Radial top_right_rad(top_rad, right_rad, fillet_steps);
    Radial top_left_rad(left_rad, top_rad, fillet_steps);
    Radial bottom_right_rad(right_rad, bottom_rad, fillet_steps);
    Radial bottom_left_rad(bottom_rad, left_rad, fillet_steps);
    Curve curve;
    curve.add(bottom_left_rad);
    curve.add(left_rad);
    curve.add(top_left_rad);
    curve.add(top_rad);
    curve.add(top_right_rad);
    curve.add(right_rad);
    curve.add(bottom_right_rad);
    curve.add(bottom_rad);
    return curve;
}

void View::build_car()
{
    Curve fc = front_curve();
    Curve bc = back_curve();
    CurveShape body1(bc, -40.0, bc, -20.0);
    CurveShape body2(bc, -20.0, fc, 0.0);
    CurveShape front(fc, 0.0);
    CurveShape back(bc, -40.0, true);
    m_aux_model->add(body1, 0.0, 0.0, 0.0);
    m_aux_model->add(body2, 0.0, 0.0, 0.0);
    m_aux_model->add(front, 0.0, 0.0, 0.0);
    m_aux_model->add(back, 0.0, 0.0, 0.0);
}

CadModel View::build_wheel(float r_tire, float r_rim, float r_inner, float r_spacer, float width)
{
    float bevel = width / 10.0;
//    PaintCan tire_p(0.0, 0.0, 0.25);
    PaintCan tire_p(1.0, 0.0, 0.0);
    PaintCan rim_p(0.75, 0.75, 0.75);
    PaintCan hub_p(1.0, 0.922, 0.0);
    PaintCan knob_p(0.25, 0.25, 0.25);
    CadModel tire = CadModel(RingShape(r_tire, r_rim, width, bevel, 0.0, bevel, 0.0), tire_p, 0.0);
    bevel = (r_rim - r_inner) / 5.0;
    CadModel rim = CadModel(RingShape(r_rim, r_inner, width, 0.0, bevel, 0.0, bevel), rim_p, 0.0);
    CadModel spacer = CadModel(RingShape(r_inner, r_spacer, width * 0.9), rim_p, 0.0);
    CadModel hub = CadModel(CylinderShape(r_spacer, width * 0.2), hub_p, 0.0);
    CadModel knob = CadModel(CylinderShape(r_rim * 0.25, width * 0.3, r_rim * 0.25 * 0.2, r_rim * 0.25 * 0.2), knob_p, 0.0);
    tire.add(rim, 0.0, 0.0, 0.0);
    tire.add(spacer, 0.0, 0.0, 0.0);
    tire.add(hub, 0.0, 0.0, 0.0);
    tire.add(knob, 0.0, 0.0, 0.0);
    return tire;
}

void View::build_wheels(float car_width)
{
    float th = TrackStyle::track_height;
    float ofs = TrackStyle::car_gap / 2.0 + TrackStyle::car_width / 2.0;
    float xofs = 3.0;
    float spacing_b = car_width * 0.825;
    float spacing_f = car_width * 0.775;
    float axle_spacing = car_width * 1.25;
    float back_radius = car_width * 0.1875;
    float front_radius = car_width * 0.16875;
    float rim_radius = car_width * 0.1125;
    float inner_radius = car_width * 0.1;
    float spacer_radius = car_width * 0.09;

    CadModel back_wheel = build_wheel(back_radius, rim_radius, inner_radius, spacer_radius, car_width * 0.2);
    CadModel front_wheel = build_wheel(front_radius, rim_radius, inner_radius, spacer_radius, car_width * 0.1375);
    m_aux_model->add(back_wheel, axle_spacing / 2.0 + xofs, -spacing_b / 2.0 + ofs, back_radius + th);
    m_aux_model->add(back_wheel, axle_spacing / 2.0 + xofs, spacing_b / 2.0 + ofs, back_radius + th);
    m_aux_model->add(front_wheel, -axle_spacing / 2.0 + xofs, -spacing_f / 2.0 + ofs, front_radius + th);
    m_aux_model->add(front_wheel, -axle_spacing / 2.0 + xofs, spacing_f / 2.0 + ofs, front_radius + th);
    m_aux_model->rotate_ax(-90.0);
}

void View::build_track()
{
    float length = 12.0;
    float radius = 6.0;
    int lanes = 2;
    CadModel s1 = CadModel(StraightTrackShape(lanes, length));
    CadModel c1 = CadModel(CurvedTrackShape(lanes, radius, 180));
    CadModel c2 = CadModel(CurvedTrackShape(lanes, radius, 180));
    s1.rotate_ay(-90);
    c1.rotate_ay(90);
    c2.rotate_ay(-90);

    m_aux_model->add(s1, 0.0, 0.0, 0.0);
    m_aux_model->add(s1, 0.0, 0.0, -2.0 * radius);
    m_aux_model->add(c1, 0.0, 0.0, 0.0);
    m_aux_model->add(c2, length, 0.0, -2.0 * radius);
}

void View::add_grid(CadModel* cm, const BoundingBox& bb)
{
    float db = 2 * Look::dimb;
    float dx = bb.vmax.v1 - bb.vmin.v1;
    float dy = 2 * Look::dimh / 20.0;
    float dz = bb.vmax.v3 - bb.vmin.v3;
    float tabley = Look::dimh / 20.0;
    int nx = round(dx);
    int nz = round(dz);
    for (int i = 0; i <= nx; i++) {
        CubeShape ls(db, dy, dz);
        CadModel line_model(ls, Look::grid_paint(), 1.0);
        cm->add(line_model, bb.vmin.v1 + (float) i, bb.vmin.v2 - tabley - 1.0, (bb.vmin.v3 + bb.vmax.v3) / 2);
    }
    for (int i = 0; i <= nz; i++) {
        CubeShape ls(dx, dy, db);
        CadModel line_model(ls, Look::grid_paint(), 1.0);
        cm->add(line_model, (bb.vmin.v1 + bb.vmax.v1) / 2, bb.vmin.v2 - tabley - 1.0, bb.vmin.v3 + (float) i);
    }
}

void View::decorate_model()
{
    BoundingBox bb = m_aux_model->bounding_box();
    float tablex = bb.vmax.v1 - bb.vmin.v1 + 4.0;
    float tabley = Look::dimh / 20.0;
    float tablez = bb.vmax.v3 - bb.vmin.v3 + 4.0;
    CubeShape table(tablex, tabley, tablez);
    CadModel tt(table, Look::table_paint(), 1.0);

    m_table = new CadModel();
    m_table->add(tt, bb.vmin.v1 + tablex / 2.0 - 2.0, bb.vmin.v2 - tabley - 1.0, bb.vmin.v3 + tablez / 2.0 - 2.0);

    bb.vmin.v1 -= 2.0;
    bb.vmin.v3 -= 2.0;
    bb.vmax.v1 += 2.0;
    bb.vmax.v3 += 2.0;

//    add_grid(m_table, bb);
    m_radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    m_radius = fmax(m_radius, (bb.vmax.v2 - bb.vmin.v2) / (2.0));
    m_radius = fmax(m_radius, 2.0);
    m_radius *= sqrt(2.0);
    m_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
    delete m_aux_model;
    m_vertex_buf.destroy();
}

bool View::initialize()
{
#ifdef VERBOSE
    printf("View::initialize()\n");
#endif
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    if (Look::get_3d())
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // gray
    else
        glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange
    if (!init_shaders())
        return false;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    resize_calc();
    m_vertex_buf.create();
    m_vertex_buf.bind();
    m_max_vertex_count = m_max_vertex_count;
    m_vertex_buf.allocate(m_max_vertex_count * sizeof(VertexData));
    copy_aux_facets();
    return true;
}

void View::sub_copy_facets(CadModel* model, VertexData* vertices, int& vix)
{
    float an_id;
    Float3 vp, vc, vn;
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        vc = model->facet_color(i);
        vn = model->facet_normal(i);
        vp = model->facet_v1(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = model->facet_v2(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = model->facet_v3(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
    }
}

void View::copy_aux_facets()
{
    m_aux_count = 3 * m_aux_model->facets();
    if (m_aux_count > 0) {
        VertexData* vertices = new VertexData[m_aux_count];
        int vix = 0;
        sub_copy_facets(m_aux_model, vertices, vix);
        // Transfer vertex data to VBO 0
        m_vertex_buf.write(0, vertices, m_aux_count * sizeof(VertexData));
        delete [] vertices;
    }
}

void View::resize(int w, int h)
{
#ifdef VERBOSE
    printf("View::resize(%d, %d)\n", w, h);
#endif
    m_width = w;
    m_height = h;
    m_aspect = qreal(w) / qreal(h ? h : 1);
    resize_calc();
}

void View::resize_calc()
{
    float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    float znear = 0.1;
    float zfar = m_camz + 2.0 * m_radius;
    m_projection.setToIdentity();
    m_projection.perspective(m_fov / m_mag, m_aspect, znear, zfar);
}

void View::check_storage()
{
    int fc = 3 * m_aux_model->facets();
    if (m_max_vertex_count > fc)
        return;
    m_max_vertex_count = std::max(2 * m_max_vertex_count, 2 * fc);
    m_vertex_buf.allocate(m_max_vertex_count * sizeof(VertexData));
}

void View::paint()
{
#ifdef VERBOSE
    printf("View::paint()\n");
#endif
    if (m_change) {
        decorate_model();
        resize_calc();
        check_storage();
        copy_aux_facets();
        m_change = false;
    }
//
// Some common things for left and right eye
//
    // Prepare rotations
    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    // Set up "between the eyes matrices
    QQuaternion my_rot = rot1 * rot2;
    QMatrix4x4 matrix;
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.rotate(my_rot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (Look::get_3d()) {
        glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE); // creates a soft red image when background is white
        QVector3D axis_y = {0.0, 1.0, 0.0};
        QQuaternion eye_rot = QQuaternion::fromAxisAndAngle(axis_y, -1);
        QQuaternion my_rot2 = eye_rot * rot1 * rot2;
        QMatrix4x4 matrix2;
        matrix2.translate(m_xoff, m_yoff, -m_camz - m_radius);
        matrix2.rotate(my_rot2);
        matrix2.translate(-m_center.v1, -m_center.v2, -m_center.v3);
        m_program.setUniformValue("mvp_matrix", m_projection * matrix2);
        m_program.setUniformValue("rot_matrix", matrix2);
    } else {
        m_program.setUniformValue("mvp_matrix", m_projection * matrix);
        m_program.setUniformValue("rot_matrix", matrix);
    }
    render_facets();
    if (Look::get_3d()) {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    }
    if (Look::get_3d()) {
        glClear(GL_DEPTH_BUFFER_BIT);
        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE); // creates a cyan image when background is white
        QVector3D axis_y = {0.0, 1.0, 0.0};
        QQuaternion eye_rot = QQuaternion::fromAxisAndAngle(axis_y, 1);
        QQuaternion my_rot2 = eye_rot * rot1 * rot2;
        QMatrix4x4 matrix2;
        matrix2.translate(m_xoff, m_yoff, -m_camz - m_radius);
        matrix2.rotate(my_rot2);
        matrix2.translate(-m_center.v1, -m_center.v2, -m_center.v3);
        m_program.setUniformValue("mvp_matrix", m_projection * matrix2);
        m_program.setUniformValue("rot_matrix", matrix2);
        render_facets();
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    }
}

void View::render_facets()
{
    // Tell OpenGL which VBOs to use
    m_vertex_buf.bind();
    // Offset for position
    quintptr offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = m_program.attributeLocation("a_position");
    m_program.enableAttributeArray(vertexLocation);
    m_program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for normal
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate normal data
    int normalLocation = m_program.attributeLocation("a_normal");
    m_program.enableAttributeArray(normalLocation);
    m_program.setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for color coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate color coordinate data
    int colorLocation = m_program.attributeLocation("a_color");
    m_program.enableAttributeArray(colorLocation);
    m_program.setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for animation_id
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate animation_id
    int animationIdLocation = m_program.attributeLocation("a_animation_id");
    m_program.enableAttributeArray(animationIdLocation);
    m_program.setAttributeBuffer(animationIdLocation, GL_FLOAT, offset, 1, sizeof(VertexData));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, m_aux_count);
}

void View::translate_x(int x)
{
    float q = tan(m_fov * (3.1415927 / 180.0) / (2.0 * m_mag));
    float wx = m_aspect * (m_camz + m_radius) * q;
    float ratio = (float) x / fmax(1.0, (float) m_width);
    float dx = wx * ratio;
    m_xoff += (      dx        );
}

void View::translate_y(int y)
{
    float q = tan(m_fov * (3.1415927 / 180.0) / (2.0 * m_mag));
    float wy = (m_camz + m_radius) * q;
    float ratio = (float) y / fmax(1.0, (float) m_height);
    float dy = wy * ratio;
    m_yoff -= (      dy        );
}

void View::translate_home()
{
    m_xoff = 0.0;
    m_yoff = 0.0;
}


void View::rotate_ax(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ax(%f)\n", degrees);
#endif
    m_xrot += degrees;
}

void View::rotate_ay(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ay(%f)\n", degrees);
#endif
    m_yrot += degrees;
}

void View::rotate_home()
{
#ifdef VERBOSE
    printf("View::rotate_home()\n");
#endif
    m_xrot = 0.0;
    m_yrot = 0.0;
}

void View::zoom(float factor)
{
    set_mag(m_mag * factor);
}

void View::zoom_home()
{
    set_mag(1.0);
}

bool View::init_shaders()
{
#ifdef VERBOSE
    printf("View::init_shaders()\n");
#endif
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        return false;
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        return false;
    if (!m_program.link())
        return false;
    if (!m_program.bind())
        return false;
    return true;
}

void View::set_mag(float mag)
{
    m_mag = fmax(1.0, mag);
    m_mag = fmin(10.0, m_mag);
    resize_calc();
}

int View::width() const
{
    return m_width;
}

int View::height() const
{
    return m_height;
}

