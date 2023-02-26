#include "view.h"
#include "paint_can.h"
#include "track.h"
#include "section.h"
#include "cube_shape.h"
#include "bounding_box.h"
#include "look.h"
#include <math.h>
#include <stdio.h>

#define notVERBOSE

View::View()
    : m_time_at_start(high_resolution_clock::now())
    , m_max_vertex_count(1024 * 1024)
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
    , m_track(new Track)
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    build_track();
    decorate_model();
    m_aux_model->add(*m_table);
    m_change = false;
}

void View::build_track()
{

    for (int i = 0; i < m_track->sections(); i++) {
        CadModel cm = m_track->section(i)->cad_model();
        m_aux_model->add(cm, 0.0, 0.0, 0.0);
    }
    CadModel car = m_track->car(0)->cad_model();
    m_aux_model->add(car, 0.0, 0.0, 0.0);
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
    delete m_track;
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
    high_resolution_clock::time_point time_in = high_resolution_clock::now();
    high_resolution_clock::duration total_period = time_in - m_time_at_start;
    m_time_at_start = time_in;
    int tp = duration_cast<nanoseconds>(total_period).count();
    m_qa.add_sample(tp);
    m_track->advance(tp);

    int car_id = 0;  // Loop for each car, factor common stuff

    // Prepare rotations
    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    QQuaternion my_rot = rot1 * rot2;
    QMatrix4x4 matrix;
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.rotate(my_rot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);
    m_program.setUniformValue("rot_matrix", matrix);
    QVector3D ani_axis1 = {0.0, 1.0, 0.0};
    QQuaternion ani_rot1 = QQuaternion::fromAxisAndAngle(ani_axis1, m_track->car_angle(car_id));
    QMatrix4x4 car_matrix;
    Double3 cp = m_track->car_position(car_id);
    car_matrix.translate(cp.v1, cp.v2, cp.v3);
    car_matrix.rotate(ani_rot1);
    m_program.setUniformValue("car_matrix", car_matrix);
    render_facets();
    glFlush();

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
    m_program.disableAttributeArray(vertexLocation);
    m_program.disableAttributeArray(normalLocation);
    m_program.disableAttributeArray(colorLocation);
    m_program.disableAttributeArray(animationIdLocation);
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



