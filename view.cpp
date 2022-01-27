#include "document.h"
#include "view.h"
#include "paint_can.h"
#include "cube_shape.h"
#include "bounding_box.h"
#include "look.h"

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
    : m_hide_force_vmenu(true)
    , m_force_vmenu()
    , m_edit_vmenu()
    , m_choose()
    , m_max_vertices(1024 * 1024)
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
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    decorate_model();
    doc->make_clean();
}

void View::mouse_unselect()
{
    m_choose.select_no_choice();
}

int View::force_vmenu_item_chosen(int sx, int sy)
{
    for (int i = 0; i < m_force_vmenu.items(); i++) {
        Face f = m_force_vmenu.face(i);
        if (screen_point_inside_face(f, sx, sy))
            return m_force_vmenu.action_id(i);
    }
    return Vmenu::ACTION_NONE;
}

int View::edit_vmenu_item_chosen(int sx, int sy)
{
    for (int i = 0; i < m_edit_vmenu.items(); i++) {
        Face f = m_edit_vmenu.face(i);
        if (screen_point_inside_face(f, sx, sy))
            return m_edit_vmenu.action_id(i);
    }
    return Vmenu::ACTION_NONE;
}

void View::mouse_select(int sx, int sy)
{
    int ix = selected_element_ix(sx, sy);
    if (ix >= 0) {
        int sf = selected_top_subface(m_doc->element(ix), sx, sy);
        const Element* e = m_doc->element(ix);
        Face f = e->top_sub_face(sf);
        Float3 p = e->get_pos();
        Choice c;
        c.position.v1 = (f.v1.v1 + f.v3.v1) / 2.0;
        if (f.v1.v2 == f.v2.v2 && f.v3.v2 == f.v4.v2 && f.v1.v2 == f.v3.v2) {  // All on same level
            c.position.v2 = e->top_level();
            c.kind = e->kind();
            c.orientation = 0;
        } else {
            c.position.v2 = e->top_level() - 0.5;
            c.kind = e->kind();
            c.orientation = e->orientation();
        }
        c.position.v3 = (f.v1.v3 + f.v3.v3) / 2.0;
        m_choose.select_choice(c);
    } else {
        BoundingBox bb = m_model->bounding_box();

        Face plane;
        float rim = 1.0;
        float xlo = bb.vmin.v1 - rim;
        float xhi = bb.vmax.v1 + rim;
        float zlo = bb.vmin.v3 - rim;
        float zhi = bb.vmax.v3 + rim;


        plane.v1.v1 = xlo;
        plane.v1.v2 = 0.0;
        plane.v1.v3 = zlo;
        plane.v2.v1 = xlo;
        plane.v2.v2 = 0.0;
        plane.v2.v3 = zhi;
        plane.v3.v1 = xhi;
        plane.v3.v2 = 0.0;
        plane.v3.v3 = zhi;
        plane.v4.v1 = xhi;
        plane.v4.v2 = 0.0;
        plane.v4.v3 = zlo;
        if (screen_point_inside_face(plane, sx, sy)) {
            if (no_part_of_any_element_selected(sx, sy)) {
                Choice c;
                c.position = screen_point_on_floor(plane, sx, sy);
                c.kind = 0;
                c.orientation = 0;
                m_choose.select_choice(c);
            } else {
                m_choose.select_no_choice();
            }

        } else {
            m_choose.select_no_choice();
        }
    }
}

int View::mouse_delete(int sx, int sy)
{
//    printf("\n\nmouse delete(%d, %d)\n", sx, sy);
    m_choose.select_no_choice();
    int ix = selected_element_ix(sx, sy);
    if (ix < 0)
        return -1;
    const Element* e = m_doc->element(ix);
    if (e == NULL)
        return -1;
    if (e->kind() == ELEMENT_ROOF)
        return ix;
    if (top_face_covered(e))
        return -1;
    return ix;
}

Float3 View::screen_point_on_floor(const Face& f, int sx, int sy) const
{
//    printf("screen_point_on_floor((%f, %f) (%f, %f))\n", f.v1.v1, f.v1.v3, f.v3.v1, f.v3.v3);
    Face box1 = f;
    Face box2 = f;
    if (fabs(f.v2.v3 - f.v1.v3) > 1.1) { // zsplit possible
//        printf("z split\n");
        float midz = (float) round((f.v2.v3 - f.v1.v3) / 2.0);
        box1.v2.v3 = f.v1.v3 + midz;
        box1.v3.v3 = f.v4.v3 + midz;
        box2.v1.v3 = f.v1.v3 + midz;
        box2.v4.v3 = f.v4.v3 + midz;
        if (screen_point_inside_face(box1, sx, sy)) {
            return screen_point_on_floor(box1, sx, sy);
        } else if (screen_point_inside_face(box2, sx, sy)) {
            return screen_point_on_floor(box2, sx, sy);
        } else {
            printf("<<< Can't zsplit because the point is in neither box. >>>\n");
            return {0.0, 0.0, 0.0};
        }
    } else if (fabs(f.v4.v1 - f.v1.v1) > 1.1) { // xsplit possible
//        printf("x split\n");
        float midx = (float) round((f.v4.v1 - f.v1.v1) / 2.0);
        box1.v4.v1 = f.v1.v1 + midx;
        box1.v3.v1 = f.v2.v1 + midx;
        box2.v1.v1 = f.v4.v1 - midx;
        box2.v2.v1 = f.v3.v1 - midx;
        if (screen_point_inside_face(box1, sx, sy)) {
            return screen_point_on_floor(box1, sx, sy);
        } else if (screen_point_inside_face(box2, sx, sy)) {
            return screen_point_on_floor(box2, sx, sy);
        } else {
            printf("<<< Can't xsplit because the point is in neither box. >>>\n");
            return {0.0, 0.0, 0.0};
        }
    } else {
//        printf("Splitting done\n");
        return {(float) round((f.v1.v1 + f.v4.v1) / 2.0), 0.0, (float) round((f.v1.v3 + f.v2.v3) / 2.0)};
    }
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

    CadModel vmenu(StlInterface(QString("vmenu_grid.stl")), Look::white_paint, 3.0);
    m_model->add(vmenu, 0.0, 0.0, 0.0);

    m_model->add(m_choose.marker_model(), 0.0, 0.0, 0.0);
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
    printf("q = %f\n", q);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    m_camz = 2.0 * m_camz / 3.0;
    m_aspect = qreal(w) / qreal(h ? h : 1);
    printf("aspect = %f\n", m_aspect);
    resize_calc();
}

void View::resize_calc()
{
//    float znear = m_camz;
    float znear = 0.1;
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

void View::paint()
{
#ifdef VERBOSE
    printf("View::paint()\n");
#endif
    if (m_doc->is_dirty() || m_force_vmenu.is_dirty() || m_edit_vmenu.is_dirty()) {
        delete m_model;
        m_model = new CadModel(m_doc);
        m_force_vmenu.add_to(m_model);
        m_edit_vmenu.add_to(m_model);
        decorate_model();
        zoom_home();
        resize_calc();
        check_storage();
        copy_facets();
        if (m_doc->is_dirty())
            m_doc->make_clean();
        if (m_force_vmenu.is_dirty())
            m_force_vmenu.make_clean();
        if (m_edit_vmenu.is_dirty())
            m_edit_vmenu.make_clean();
        m_choose.select_no_choice();
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
    if (m_choose.marker_visible()) {
        Float3 mp = m_choose.marker_position();
        marker_matrix.translate(mp.v1, mp.v2 * 2.0 / 3.0, mp.v3);
        float angle = m_choose.marker_angle();
        int orientation = m_choose.marker_orientation();
        if (angle > 0.0) {
            QVector3D axis3;
            if (orientation & 1)
                axis3 = {0.0, 0.0, 1.0};
            else
                axis3 = {1.0, 0.0, 0.0};
            if (orientation == 1 || orientation == 2)
                angle = -angle;
            QQuaternion rot3 = QQuaternion::fromAxisAndAngle(axis3, angle);
            marker_matrix.rotate(rot3);
        }

    } else {
        marker_matrix.translate(m_center.v1, -0.04, m_center.v3);
    }
    m_program.setUniformValue("marker_matrix", marker_matrix);

    QMatrix4x4 vmenu_matrix;
    float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
    float dy = 0.45;
    float dz = 1.2;
    float dx = m_hide_force_vmenu ? - 0.11 : 0.0;
    vmenu_matrix.translate(dx + -dz * q * m_aspect,dz * q - dy, -dz);
    vmenu_matrix = m_projection * vmenu_matrix;
    m_program.setUniformValue("vmenu_matrix", vmenu_matrix);
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

Float2 View::world2screen(Float3 point, float* distance) const
{
    Float2 res;
    QVector4D sp = m_mvp_matrix * QVector4D(point.v1, point.v2, point.v3, 1.0);
    res.v1 = m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w()));
    res.v2 = m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w()));
    if (distance != NULL)
        *distance = sp.z();
    return res;
}

float View::min4(float a, float b, float c, float d) const
{
    float u = std::min(a, b);
    float v = std::min(c, d);
    return std::min(u, v);
}

float View::max4(float a, float b, float c, float d) const
{
    float u = std::max(a, b);
    float v = std::max(c, d);
    return std::max(u, v);
}

bool View::screen_point_inside_face(const Face& f, int sx, int sy, float* depth) const
{
    // transform the four vertices of f
    float distance;
    Float2 a = world2screen({f.v1.v1, f.v1.v2, f.v1.v3}, &distance);
    float zbuf = distance;
    Float2 b = world2screen({f.v2.v1, f.v2.v2, f.v2.v3}, &distance);
    zbuf += distance;
    Float2 c = world2screen({f.v3.v1, f.v3.v2, f.v3.v3}, &distance);
    zbuf += distance;
    Float2 d = world2screen({f.v4.v1, f.v4.v2, f.v4.v3}, &distance);
    zbuf += distance;
    if (depth != NULL)
        *depth = zbuf / 4.0;
    Float2 pt = {(float) sx, (float) sy};

    float xmin = min4(a.v1, b.v1, c.v1, d.v1);
    float xmax = max4(a.v1, b.v1, c.v1, d.v1);
    float ymin = min4(a.v2, b.v2, c.v2, d.v2);
    float ymax = max4(a.v2, b.v2, c.v2, d.v2);
    if (pt.v1 < xmin || pt.v1 > xmax)
        return false;
    if (pt.v2 < ymin || pt.v2 > ymax)
        return false;
    double area1 = tri_area(a, b, pt) + tri_area(b, c, pt) + tri_area(c, d, pt) + tri_area(d, a, pt);
    double area2 = quad_area(a, b, c, d);
    return area1 <= (area2 + 1.00);
}

double View::len(Float2 v1, Float2 v2) const
{
    double a = v1.v1 - v2.v1;
    double b = v1.v2 - v2.v2;
    return sqrt(a * a + b * b);
}

double View::tri_area(Float2 v1, Float2 v2, Float2 v3) const
{
    double a = len(v1, v2);
    double b = len(v2, v3);
    double c = len(v3, v1);
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double View::quad_area(Float2 v1, Float2 v2, Float2 v3, Float2 v4) const
{
    double a = len(v1, v2);
    double b = len(v2, v3);
    double c = len(v3, v4);
    double d = len(v4, v1);
    double p = len(v1, v3);
    double q = len(v2, v4);
    double k = b * b + d * d - a * a - c * c;
    return sqrt(4.0 * p * p * q * q - k * k) / 4.0;
}

bool View::no_part_of_any_element_selected(int sx, int sy) const
{
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        for (int j = 0; j < 6; j++) {
            Face f = e->face(j);
            if (screen_point_inside_face(f, sx, sy))
                return false;
        }
    }
    return true;
}

float View::normalize_angle(float angle) const
{
    float a = angle;
    while (a < 0.0)
        a += 360.0;
    while (a >= 360.0)
        a -= 360.0;
    return a;
}

int View::selected_element_ix(int sx, int sy) const
{
    float min_depth = 1000000.0;
    float max_level = -1000000.0;
    const Element* min_e = NULL;
    int min_ix = -1;
    float depth;

    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (screen_point_inside_face(e->face(TOP_FACE), sx, sy, &depth)) {
            if (depth < min_depth || e->top_level() > max_level) {
                if (depth < min_depth)
                    min_depth = depth;
                if (e->top_level() > max_level)
                    max_level = e->top_level();
                min_e = e;
                min_ix = i;
            }
        }
    }
    if (min_e == NULL)
        return -1;
    int sf = selected_top_subface(min_e, sx, sy);
    return top_subface_covered(min_e, sf) ? -1 : min_ix;
}

int View::selected_top_subface(const Element* e, int sx, int sy) const
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
    pos.v2 = e->top_level() + 0.25;
    pos.v3 = (sf.v1.v3 + sf.v3.v3) / 2.0;
    return m_doc->contains(pos);
}

bool View::gap_below_span(Float3 pos, int span, int orientation) const
{
    if (span < 2)
        return false;
    float half_width = ((float) span + 1.0) / 2.0;
    for (int i = 1; i < span; i++) {
        Float3 tpos = pos;
        if (orientation & 1)
            tpos.v3 = 0.5 + pos.v3 - half_width + (float) i;
        else
            tpos.v1 = 0.5 + pos.v1 - half_width + (float) i;
        tpos.v2 -= 0.25;
        if (!m_doc->contains(tpos))
            return true; // At least one gap
    }
    return false;
}

bool View::span_blocked(Float3 pos, int span, int orientation) const
{
    if (span < 2)
        return false;
    float half_width = ((float) span + 1.0) / 2.0;
    for (int i = 1; i < span; i++) {
        Float3 tpos = pos;
        if (orientation & 1)
            tpos.v3 = 0.5 + pos.v3 - half_width + (float) i;
        else
            tpos.v1 = 0.5 + pos.v1 - half_width + (float) i;
        tpos.v2 += 0.25;
        if (m_doc->contains(tpos)) {
            printf("     blocked because doc contains (%f, %f, %f)\n", tpos.v1, tpos.v2, tpos.v3);
            return true; // At least one element
        }
    }
    return false;
}

bool View::element_is_above_span(const Element* e, Float3 pos, int span, int orientation) const
{
    if (e->get_pos().v2 <= pos.v2)
        return false;
    if (orientation == 0 || orientation == 2) { // cases 2 and 3
        float width = span + 1;
        float span_xlo = pos.v1 - width / 2 + 1;
        float span_xhi = pos.v1 + width / 2 - 1;
        float span_z = pos.v3;
        if (e->orientation() == 0 || e->orientation() == 2) {  // case 3
            float ewidth = e->width();
            float e_xlo = e->get_pos().v1 - ewidth / 2;
            float e_xhi = e->get_pos().v1 + ewidth / 2;
            float e_z = e->get_pos().v3;
            return (e_z == span_z) && (span_xhi >= e_xlo && span_xlo <= e_xhi);
        } else {                                              // case 2
            float ewidth = e->width();
            float e_zlo = e->get_pos().v3 - ewidth / 2;
            float e_zhi = e->get_pos().v3 + ewidth / 2;
            float e_x = e->get_pos().v1;
            return (e_zlo <= span_z && e_zhi >= span_z) && (span_xlo <= e_x && span_xhi >= e_x);
        }
    } else {                                    // cases 1 and 4
        float width = span + 1;
        float span_zlo = pos.v3 - width / 2 + 1;
        float span_zhi = pos.v3 + width / 2 - 1;
        float span_x = pos.v1;
        if (e->orientation() == 0 || e->orientation() == 2) {  // case 1
            float ewidth = e->width();
            float e_xlo = e->get_pos().v1 - ewidth / 2;
            float e_xhi = e->get_pos().v1 + ewidth / 2;
            float e_z = e->get_pos().v3;
            return (span_zlo <= e_z && span_zhi >= e_z) && (e_xlo <= span_x && e_xhi >= span_x);
        } else {                                              // case 4
            float ewidth = e->width();
            float e_zlo = e->get_pos().v3 - ewidth / 2;
            float e_zhi = e->get_pos().v3 + ewidth / 2;
            float e_x = e->get_pos().v1;
            return (e_x == span_x) && (span_zhi >= e_zlo && span_zlo <= e_zhi);
        }
    }
    return false;
}

int View::span_clearance(Float3 pos, int span, int orientation) const // return 0 means infinite clearance
{
    if (span < 2)
        return 0;
    float min_height = 0.0;
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (e->kind() == ELEMENT_LEDGE) {
            if (element_is_above_span(e, pos, span, orientation)) {
                if (min_height == 0.0)
                    min_height = e->get_pos().v2;
                else
                    min_height = fmin(e->get_pos().v2, min_height);
            }
        }
    }
    float clearance = min_height;
    if (clearance > 0.0)
        clearance -= (pos.v2 + 0.5);
    return round(clearance);
}

bool View::new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool& roof)
{
    return m_choose.new_element_chosen(pos, span, orientation, same_level, roof);
}

Vmenu& View::get_force_vmenu()
{
    return m_force_vmenu;
}

Vmenu& View::get_edit_vmenu()
{
    return m_edit_vmenu;
}

void View::toggle_force_vmenu()
{
    m_hide_force_vmenu = !m_hide_force_vmenu;
}

bool View::force_vmenu_hidden() const
{
    return m_hide_force_vmenu;
}

