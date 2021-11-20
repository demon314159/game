#include "document.h"
#include "view.h"
#include "paint_can.h"
#include "cube_shape.h"
#include "bounding_box.h"

#include <math.h>
#include <stdio.h>

#define notVERBOSE

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    float animation_id;
};

View::View(Document* doc)
    : m_max_vertices(1024 * 1024)
    , m_vertices(0)
    , m_doc(doc)
    , m_model(new CadModel(doc))
    , m_radius(2.0)
    , m_center({0.0, 0.0, 0.0})
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_aspect(1.0)
    , m_fov(45.0)
    , m_camz(8.0)
    , m_xrot(0.0)
    , m_yrot(0.0)
    , m_marker_flag(false)
    , m_marker_pos({0.0, 0.0, 0.0})
    , m_marker_model(CadModel(StlInterface(QString("marker.stl")),PaintCan(0.0, 1.0, 0.0), 2.0))
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    decorate_model();
    doc->make_clean();
}

void View::mouse_select(int sx, int sy)
{
    printf("mouse select(%d, %d)\n", sx, sy);
//    float max_level = -1.0;
//    Float3 sel_pos = {0.0, 0.0, 0.0};
}

void View::decorate_model()
{
//    printf("%d facets\n", m_model->facets());
    BoundingBox bb = m_model->bounding_box();
    float tablex = bb.vmax.v1 - bb.vmin.v1 + 2.0;
    float tabley = Element::dimh / 20.0;
    float tablez = bb.vmax.v3 - bb.vmin.v3 + 2.0;
    CubeShape table(tablex, tabley, tablez);
    CadModel tt(table, PaintCan(0.4, 0.8, 1.0), 1.0);
    m_model->add(tt, bb.vmin.v1 + tablex / 2.0 - 1.0, -tabley, bb.vmin.v3 + tablez / 2 - 1.0);
    bb = m_model->bounding_box();
    m_model->add(m_marker_model, 0.0, 0.0, 0.0);
    m_radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    m_radius = fmax(m_radius, fabs(bb.vmax.v2 - bb.vmin.v2) / 2.0 );
    m_radius = fmax(m_radius, 2.0);
    m_radius *= 1.5;
    m_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
    delete m_model;
    delete m_doc;
    m_vertex_buf.destroy();
}

Document* View::get_doc() const
{
    return m_doc;
}

Document* View::replace_doc(Document* doc)
{
    Document* t;
    t = m_doc;
    m_doc = doc;
    return t;
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
    resize_calc();
    m_vertex_buf.create();
    m_vertex_buf.bind();
    m_max_vertices = std::max(m_max_vertices, 6 * m_model->facets());
    m_vertex_buf.allocate(m_max_vertices * sizeof(VertexData));
    copy_facets();
    return true;
}

void View::copy_facets()
{
    m_vertices = 3 * m_model->facets();
    if (m_vertices == 0) {
        return;
    }
    VertexData* vertices = new VertexData[m_vertices];
    float an_id;
    Float3 vp, vc, vn;
    int vix = 0;
    for (int i = 0; i < m_model->facets(); i++) {
        an_id = m_model->facet_animation_id(i);
        vc = m_model->facet_color(i);
        vn = m_model->facet_normal(i);
        vp = m_model->facet_v1(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = m_model->facet_v2(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
        vp = m_model->facet_v3(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = QVector3D(vp.v1, vp.v2, vp.v3);
        vertices[vix].normal = QVector3D(vn.v1, vn.v2, vn.v3);
        vertices[vix++].color = QVector3D(vc.v1, vc.v2, vc.v3);
    }
    // Transfer vertex data to VBO 0
    m_vertex_buf.write(0, vertices, m_vertices * sizeof(VertexData));
    delete [] vertices;
}

void View::resize(int w, int h)
{
#ifdef VERBOSE
    printf("View::resize(%d, %d)\n", w, h);
#endif
    m_width = w;
    m_height = h;
    float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    m_camz = 2.0 * m_camz / 3.0;
    m_aspect = qreal(w) / qreal(h ? h : 1);
    resize_calc();
}

void View::resize_calc()
{
    float znear = m_camz;
    float zfar = m_camz + 2.0 * m_radius;
    m_projection.setToIdentity();
    m_projection.perspective(m_fov, m_aspect, znear, zfar);
}

void View::check_storage()
{
    if (m_max_vertices > (3 * m_model->facets()))
        return;
    m_max_vertices = std::max(2 * m_max_vertices, 6 * m_model->facets());
    m_vertex_buf.allocate(m_max_vertices * sizeof(VertexData));
}

void View::clear_marker()
{
    m_marker_flag = false;
}

void View::paint()
{
#ifdef VERBOSE
    printf("View::paint()\n");
#endif
    if (m_doc->is_dirty()) {
        delete m_model;
        m_model = new CadModel(m_doc);
        decorate_model();
        resize_calc();
        check_storage();
        copy_facets();
        m_doc->make_clean();
        clear_marker();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    QQuaternion my_rot = rot1 * rot2;
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -m_camz - m_radius);
    matrix.rotate(my_rot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    // Set modelview-projection matrix
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    m_program.setUniformValue("mvp_matrix", m_projection * matrix);
    m_program.setUniformValue("rot_matrix", matrix);
    // Animate marker
    QMatrix4x4 marker_matrix;
    if (m_marker_flag) {
        marker_matrix.translate(m_marker_pos.v1, (m_marker_pos.v2 - 0.5) * 2.0 / 3.0, m_marker_pos.v3);
    } else {
        marker_matrix.translate(m_center.v1, -0.04, m_center.v3);
    }
    m_program.setUniformValue("marker_matrix", marker_matrix);
    // Draw the model
    render_facets();
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

    glDrawArrays(GL_TRIANGLES, 0, m_vertices);
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
#ifdef VERBOSE
    printf("View::zoom(%f)\n", factor);
#endif
    m_camz *= factor;
    resize_calc();
}

void View::zoom_home()
{
#ifdef VERBOSE
    printf("View::zoom_home()\n");
#endif
    float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    m_camz = 2.0 * m_camz / 3.0;
    resize_calc();
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

Float2 View::world2screen(Float3 point) const
{
    Float2 res;
    QVector4D sp = m_mvp_matrix * QVector4D(point.v1, point.v2, point.v3, 1.0);
    res.v1 = m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w()));
    res.v2 = m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w()));
    return res;
}

bool View::screen_point_inside_face(const Face& f, int sx, int sy) const
{
    // transform the four vertices of f
    // perform the four cross products in counter clockwise order
    Float2 a = world2screen({f.v1.v1, f.v1.v2, f.v1.v3});
    Float2 b = world2screen({f.v2.v1, f.v2.v2, f.v2.v3});
    Float2 c = world2screen({f.v3.v1, f.v3.v2, f.v3.v3});
    Float2 d = world2screen({f.v4.v1, f.v4.v2, f.v4.v3});
    int cp1 = screen_cross_product(a, b, sx, sy);
    int cp2 = screen_cross_product(b, c, sx, sy);
    int cp3 = screen_cross_product(c, d, sx, sy);
    int cp4 = screen_cross_product(d, a, sx, sy);
    return (cp1 < 0 && cp2 < 0 && cp3 < 0 && cp4 < 0);
}

int View::screen_cross_product(Float2 a, Float2 b, int sx, int sy) const
{
    int ax = a.v1 - sx;
    int ay = a.v2 - sy;
    int bx = b.v1 - sx;
    int by = b.v2 - sy;
    return ax * by - bx * ay;
}

const Element* View::selected_element(int sx, int sy) const
{
    float max_level = -1000000.0;
    const Element* max_e = NULL;

    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (screen_point_inside_face(e->top_face(), sx, sy)) {
            if (e->top_level() > max_level) {
                max_level = e->top_level();
                max_e = e;
            }
        }
    }
    return max_e;
}

int View::selected_subface(const Element* e, int sx, int sy) const
{
    if (e == NULL)
        return 0;
    for (int i = 0; i < e->sub_face_count(); i++)
        if (screen_point_inside_face(e->top_sub_face(i), sx, sy))
            return i;
    return 0;
}

bool View::top_face_covered(const Element* e) const
{
    if (e == NULL)
        return true;
    for (int i = 0; i < e->sub_face_count(); i++)
        if (top_subface_covered(e, i))
            return true;
    return false;
}

bool View::top_subface_covered(const Element* e, int ix) const
{
    if (e == NULL)
        return true;
    Face sf = e->top_sub_face(ix);
    Float3 pos;
    pos.v1 = (sf.v1.v1 + sf.v3.v1) / 2.0;
    pos.v2 = e->top_level() + 0.5;
    pos.v3 = (sf.v1.v3 + sf.v3.v3) / 2.0;
    for (int i = 0; i < m_doc->elements(); i++) {
        if (m_doc->element(i)->contains(pos))
            return true;
    }
    return false;
}

