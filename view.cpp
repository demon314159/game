#include "document.h"
#include "view.h"
#include "paint_can.h"
#include "cube_shape.h"
#include "bounding_box.h"
#include "look.h"

#include <math.h>
#include <stdio.h>

#define notVERBOSE

View::View(Document* doc)
    : m_vmenu()
    , m_choose()
    , m_max_vertex_count(1024 * 1024)
    , m_building_count(0)
    , m_glass_count(0)
    , m_aux_count(0)
    , m_doc(doc)
    , m_table(new CadModel())
    , m_aux_model(new CadModel())
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
    decorate_model();
    m_aux_model->add(*m_table);
    doc->clear_changes();
}

void View::mouse_unselect()
{
    m_choose.select_no_choice();
}

int View::vmenu_item_chosen(int sx, int sy)
{
    for (int i = 0; i < m_vmenu.items(); i++) {
        Face f = m_vmenu.face(i);
        if (m_vmenu.fixed(i)) {
            if (screen_point_inside_fixed_face(f, sx, sy))
                return m_vmenu.action_id(i);
        }
        else {
            if (screen_point_inside_face(f, sx, sy))
                return m_vmenu.action_id(i);
        }
    }
    return Vmenu::ACTION_NONE;
}

bool View::mouse_select(int sx, int sy)
{
    MouseVector tmv = new_mouse_vector(sx, sy);
    int ix = selected_element_ix(sx, sy, tmv);
    if (ix >= 0) {
        int sf = selected_top_subface(m_doc->element(ix), sx, sy);
        const Element* e = m_doc->element(ix);
        Face f = e->top_sub_face(sf);
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
        return true;
    } else {
        if (tmv.vector().v2 != 0.0) {
            BoundingBox bb = m_doc->bounding_box(true);
            bb.vmin.v1 -= 2.0;
            bb.vmin.v3 -= 2.0;
            bb.vmax.v1 += 2.0;
            bb.vmax.v3 += 2.0;
            float xlo = truncf(bb.vmin.v1);
            float xhi = truncf(bb.vmax.v1);
            float zlo = truncf(bb.vmin.v3);
            float zhi = truncf(bb.vmax.v3);
            float t = -tmv.origin().v2 / tmv.vector().v2;
            float x = roundf(tmv.origin().v1 + t * tmv.vector().v1);
            float z = roundf(tmv.origin().v3 + t * tmv.vector().v3);
            if (x >= xlo && x <= xhi && z >= zlo && z <= zhi) {
                if (no_part_of_any_element_selected(sx, sy, tmv)) {
                    Choice c;
                    c.position = {x, 0.0, z};
                    c.kind = 0;
                    c.orientation = 0;
                    m_choose.select_choice(c);
                    return true;
                } else {
                    m_choose.select_no_choice();
                }

            } else {
                m_choose.select_no_choice();
            }

        } else {
            m_choose.select_no_choice();
        }
    }
    return false;
}

int View::mouse_delete(int sx, int sy)
{
    m_choose.select_no_choice();
    MouseVector tmv = new_mouse_vector(sx, sy);
    int ix = selected_element_ix(sx, sy, tmv);
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

void View::add_grid(CadModel* cm, const BoundingBox& bb)
{
    float db = 2 * Element::dimb;
    float dx = bb.vmax.v1 - bb.vmin.v1;
    float dy = 2 * Element::dimh / 20.0;
    float dz = bb.vmax.v3 - bb.vmin.v3;
    float tabley = Element::dimh / 20.0;
    int nx = round(dx);
    int nz = round(dz);
    for (int i = 0; i <= nx; i++) {
        CubeShape ls(db, dy, dz);
        CadModel line_model(ls, Look::grid_paint, 1.0);
        cm->add(line_model, bb.vmin.v1 + (float) i, -tabley, (bb.vmin.v3 + bb.vmax.v3) / 2);
    }
    for (int i = 0; i <= nz; i++) {
        CubeShape ls(dx, dy, db);
        CadModel line_model(ls, Look::grid_paint, 1.0);
        cm->add(line_model, (bb.vmin.v1 + bb.vmax.v1) / 2, -tabley, bb.vmin.v3 + (float) i);
    }
}

void View::decorate_model()
{
    BoundingBox bb = m_doc->bounding_box(true);
    float tablex = bb.vmax.v1 - bb.vmin.v1 + 4.0;
    float tabley = Element::dimh / 20.0;
    float tablez = bb.vmax.v3 - bb.vmin.v3 + 4.0;
    CubeShape table(tablex, tabley, tablez);
    CadModel tt(table, PaintCan(0.4, 0.8, 1.0), 1.0);

    delete m_table;
    m_table = new CadModel();
    m_table->add(tt, bb.vmin.v1 + tablex / 2.0 - 2.0, -tabley, bb.vmin.v3 + tablez / 2 - 2.0);

    bb.vmin.v1 -= 2.0;
    bb.vmin.v3 -= 2.0;
    bb.vmax.v1 += 2.0;
    bb.vmax.v3 += 2.0;

    add_grid(m_table, bb);
    m_table->add(m_choose.marker_model(), 0.0, 0.0, 0.0);
    m_radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    m_radius = fmax(m_radius, (bb.vmax.v2 - bb.vmin.v2) / (2.0 * Element::dimh));
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    resize_calc();
    m_vertex_buf.create();
    m_vertex_buf.bind();
    m_max_vertex_count = std::max(m_max_vertex_count, 2 * m_doc->building().vertex_count());
    m_vertex_buf.allocate(m_max_vertex_count * sizeof(VertexData));
    copy_vertices();

    copy_aux_facets();
    return true;
}

void View::copy_vertices()
{
    m_building_count = m_doc->building().vertex_count();
    if (m_building_count == 0) {
        return;
    }
    const VertexData* vertices = m_doc->building().vertex_data();
    // Transfer vertex data to VBO 0
    m_vertex_buf.write(0, vertices, m_building_count * sizeof(VertexData));
}

void View::copy_changed_vertices()
{
    m_building_count = m_doc->building().vertex_count();  // In case this has grown with add_element()
    int ix = m_doc->changed_ix();
    if (ix < m_doc->elements()) {
        int this_start = m_doc->building_index(ix);
        int next_start = m_doc->building_index(ix + 1); // This works when ix + 1 is beyond last element
        int n = next_start - this_start;
        const VertexData* vertices = m_doc->building().vertex_data();
        // Transfer vertex data to VBO 0
        m_vertex_buf.write(this_start * sizeof(VertexData), vertices + this_start, n * sizeof(VertexData));
    }
}

void View::sub_copy_facets(CadModel* model, VertexData* vertices, int& vix, bool transparent)
{
    float an_id;
    Float3 vp, vc, vn;
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        if ((transparent && (an_id == 99.0)) || (!transparent && (an_id != 99.0))) {
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
}

void View::copy_aux_facets()
{
    m_aux_count = 3 * m_aux_model->facets();
    if (m_aux_count > 0) {
        VertexData* vertices = new VertexData[m_aux_count];
        int vix = 0;
        sub_copy_facets(m_aux_model, vertices, vix, false);
        sub_copy_facets(m_aux_model, vertices, vix, true);
        // Transfer vertex data to VBO 0
        m_vertex_buf.write(m_building_count * sizeof(VertexData), vertices, m_aux_count * sizeof(VertexData));
        delete [] vertices;
    }
    m_glass_count = m_doc->glass().vertex_count();
    if (m_glass_count == 0) {
        return;
    }
    const VertexData* vertices = m_doc->glass().vertex_data();
    // Transfer vertex data to VBO 0
    m_vertex_buf.write((m_building_count + m_aux_count) * sizeof(VertexData), vertices, m_glass_count * sizeof(VertexData));
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
    int fc = 3 * m_doc->facets();
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
    if (m_doc->just_one_change() || m_doc->many_changes()) {
        decorate_model();
        if (m_doc->many_changes()) {
            zoom_home();
            translate_home();
        }
        resize_calc();
        check_storage();
        if (m_doc->just_one_change()) {
            copy_changed_vertices();
        } else {
            copy_vertices();
        }
        m_vmenu.make_dirty();
        m_doc->clear_changes();
        m_choose.select_no_choice();
    }
    if (m_vmenu.is_dirty()) {
        delete m_aux_model;
        m_aux_model = new CadModel();
        m_aux_model->add(*m_table);
        m_vmenu.add_to(m_aux_model);
        copy_aux_facets();
        if (m_vmenu.is_dirty())
            m_vmenu.make_clean();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);

    QQuaternion my_rot = rot1 * rot2;
//    QQuaternion my_rot = rot2 * rot1;


    QMatrix4x4 matrix;
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
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

    m_fixed_matrix = QMatrix4x4();
    float q = tan(m_fov * (3.1415927 / 180.0) / (2.0 * m_mag));
    float dz = 1.2;
    m_fixed_matrix.translate(dz * q * m_aspect, dz * q, -dz);
    m_fixed_matrix = m_projection * m_fixed_matrix;
    m_program.setUniformValue("fixed_matrix", m_fixed_matrix);
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

    glDrawArrays(GL_TRIANGLES, 0, m_building_count + m_aux_count + m_glass_count);
}

void View::translate_x(int x)
{
    m_xoff += (((float) x) / 64.0);
}

void View::translate_y(int y)
{
    m_yoff -= (((float) y) / 64.0);
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

Float2 View::fixed2screen(Float3 point) const
{
    Float2 res;
    QVector4D sp = m_fixed_matrix * QVector4D(point.v1, point.v2, point.v3, 1.0);
    res.v1 = m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w()));
    res.v2 = m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w()));
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

bool View::screen_point_inside_fixed_face(const Face& f, int sx, int sy) const
{
    // transform the four vertices of f
    Float2 a = fixed2screen({f.v1.v1, f.v1.v2, f.v1.v3});
    Float2 b = fixed2screen({f.v2.v1, f.v2.v2, f.v2.v3});
    Float2 c = fixed2screen({f.v3.v1, f.v3.v2, f.v3.v3});
    Float2 d = fixed2screen({f.v4.v1, f.v4.v2, f.v4.v3});
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

MouseVector View::new_mouse_vector(int sx, int sy) const
{
    double camy = m_camz * tan((3.1415926536 / 180.0) * m_fov / (2 * m_mag));
    double k = 2 * camy / (double) m_height;
    float v1 = k * ((double) sx - ((double) m_width) / 2);
    float v2 = k * (-(double) sy + ((double) m_height) / 2);
    Float3 vector = {v1 / m_camz, v2 / m_camz, -1.0};
    Float3 origin = {0.0, 0.0, 0.0};
    MouseVector tmv(origin, vector);
    tmv.translate({-m_xoff, -m_yoff, m_camz + m_radius});
    tmv.rotate_ax(m_xrot);
    tmv.rotate_ay(m_yrot);
    tmv.translate(m_center);
    return tmv;
}

bool View::mouse_vector_intersects(const MouseVector& mv, const Face& f) const
{
    Float3 mv_org = mv.origin();
    Float3 mv_vec = mv.vector();
    float abs_v1 = fabs(mv_vec.v1);
    float abs_v2 = fabs(mv_vec.v2);
    float abs_v3 = fabs(mv_vec.v3);
    if (abs_v3 > abs_v1 && abs_v3 > abs_v2) {        // Z is dominant axis
        float zface = (f.v1.v3 + f.v2.v3 + f.v3.v3 + f.v4.v3) / 4.0;
        float t = (zface - mv_org.v3) / mv_vec.v3;
        float x = mv_org.v1 + t * mv_vec.v1;
        float y = mv_org.v2 + t * mv_vec.v2;
        if (x < f.v1.v1 && x < f.v2.v1 && x < f.v3.v1 && x < f.v4.v1)
            return false;
        if (x > f.v1.v1 && x > f.v2.v1 && x > f.v3.v1 && x > f.v4.v1)
            return false;
        if (y < f.v1.v2 && y < f.v2.v2 && y < f.v3.v2 && y < f.v4.v2)
            return false;
        if (y > f.v1.v2 && y > f.v2.v2 && y > f.v3.v2 && y > f.v4.v2)
            return false;
        return true;
    } else if (abs_v2 > abs_v1 && abs_v2 > abs_v3) { // Y is dominant axis
        float yface = (f.v1.v2 + f.v2.v2 + f.v3.v2 + f.v4.v2) / 4.0;
        float t = (yface - mv_org.v2) / mv_vec.v2;
        float x = mv_org.v1 + t * mv_vec.v1;
        float z = mv_org.v3 + t * mv_vec.v3;
        if (x < f.v1.v1 && x < f.v2.v1 && x < f.v3.v1 && x < f.v4.v1)
            return false;
        if (x > f.v1.v1 && x > f.v2.v1 && x > f.v3.v1 && x > f.v4.v1)
            return false;
        if (z < f.v1.v3 && z < f.v2.v3 && z < f.v3.v3 && z < f.v4.v3)
            return false;
        if (z > f.v1.v3 && z > f.v2.v3 && z > f.v3.v3 && z > f.v4.v3)
            return false;
        return true;
    } else {                                         // X is dominant axis
        float xface = (f.v1.v1 + f.v2.v1 + f.v3.v1 + f.v4.v1) / 4.0;
        float t = (xface - mv_org.v1) / mv_vec.v1;
        float y = mv_org.v2 + t * mv_vec.v2;
        float z = mv_org.v3 + t * mv_vec.v3;
        if (y < f.v1.v2 && y < f.v2.v2 && y < f.v3.v2 && y < f.v4.v2)
            return false;
        if (y > f.v1.v2 && y > f.v2.v2 && y > f.v3.v2 && y > f.v4.v2)
            return false;
        if (z < f.v1.v3 && z < f.v2.v3 && z < f.v3.v3 && z < f.v4.v3)
            return false;
        if (z > f.v1.v3 && z > f.v2.v3 && z > f.v3.v3 && z > f.v4.v3)
            return false;
        return true;
    }
}

bool View::mouse_vector_intersects(const MouseVector& mv, const Element* e) const
{
    Float3 mv_org = mv.origin();
    Float3 mv_vec = mv.vector();
    BoundingBox bb = e->bounding_box();
    float abs_v1 = fabs(mv_vec.v1);
    float abs_v2 = fabs(mv_vec.v2);
    float abs_v3 = fabs(mv_vec.v3);
    if (abs_v3 > abs_v1 && abs_v3 > abs_v2) {        // Z is dominant axis
        float tmin = (bb.vmin.v3 - mv_org.v3) / mv_vec.v3;
        float tmax = (bb.vmax.v3 - mv_org.v3) / mv_vec.v3;
        float xmin = mv_org.v1 + tmin * mv_vec.v1;
        float xmax = mv_org.v1 + tmax * mv_vec.v1;
        float ymin = mv_org.v2 + tmin * mv_vec.v2;
        float ymax = mv_org.v2 + tmax * mv_vec.v2;
        if (xmin < bb.vmin.v1 && xmax < bb.vmin.v1)
            return false;
        if (xmin > bb.vmax.v1 && xmax > bb.vmax.v1)
            return false;
        if (ymin < bb.vmin.v2 && ymax < bb.vmin.v2)
            return false;
        if (ymin > bb.vmax.v2 && ymax > bb.vmax.v2)
            return false;
        return true;
    } else if (abs_v2 > abs_v1 && abs_v2 > abs_v3) { // Y is dominant axis
        float tmin = (bb.vmin.v2 - mv_org.v2) / mv_vec.v2;
        float tmax = (bb.vmax.v2 - mv_org.v2) / mv_vec.v2;
        float xmin = mv_org.v1 + tmin * mv_vec.v1;
        float xmax = mv_org.v1 + tmax * mv_vec.v1;
        float zmin = mv_org.v3 + tmin * mv_vec.v3;
        float zmax = mv_org.v3 + tmax * mv_vec.v3;
        if (xmin < bb.vmin.v1 && xmax < bb.vmin.v1)
            return false;
        if (xmin > bb.vmax.v1 && xmax > bb.vmax.v1)
            return false;
        if (zmin < bb.vmin.v3 && zmax < bb.vmin.v3)
            return false;
        if (zmin > bb.vmax.v3 && zmax > bb.vmax.v3)
            return false;
        return true;
    } else {                                         // X is dominant axis
        float tmin = (bb.vmin.v1 - mv_org.v1) / mv_vec.v1;
        float tmax = (bb.vmax.v1 - mv_org.v1) / mv_vec.v1;
        float ymin = mv_org.v2 + tmin * mv_vec.v2;
        float ymax = mv_org.v2 + tmax * mv_vec.v2;
        float zmin = mv_org.v3 + tmin * mv_vec.v3;
        float zmax = mv_org.v3 + tmax * mv_vec.v3;
        if (ymin < bb.vmin.v2 && ymax < bb.vmin.v2)
            return false;
        if (ymin > bb.vmax.v2 && ymax > bb.vmax.v2)
            return false;
        if (zmin < bb.vmin.v3 && zmax < bb.vmin.v3)
            return false;
        if (zmin > bb.vmax.v3 && zmax > bb.vmax.v3)
            return false;
        return true;
    }
}

bool View::no_part_of_any_element_selected(int sx, int sy, const MouseVector& mv) const
{
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (!e->removed()) {
            if (mouse_vector_intersects(mv, e)) { // Very quick test to eliminate most candidates
                for (int j = 0; j < 6; j++) {
                    Face f = e->face(j);
                    if (screen_point_inside_face(f, sx, sy)) {  // Very expensive test times 6 for each candidate
                        return false;
                    }
                }
            }
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

int View::selected_element_ix(int sx, int sy, const MouseVector& mv) const
{
    float min_depth = 1000000.0;
    float max_level = -1000000.0;
    const Element* min_e = NULL;
    int min_ix = -1;
    int min_face = 0;
    float depth;

    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (!e->removed()) {
            if (mouse_vector_intersects(mv, e)) { // Very quick test to eliminate most candidates
                for (int j = 0; j < 6; j++) {
                    if (screen_point_inside_face(e->face(j), sx, sy, &depth)) {  // Very expensive test
                        if (depth < min_depth) {
                            if (depth < min_depth)
                                min_depth = depth;
                            if (e->top_level() > max_level)
                                max_level = e->top_level();
                            min_e = e;
                            min_ix = i;
                            min_face = j;
                        }
                    }

                }

            }
        }
    }
    if (min_e == NULL)
        return -1;
    if (min_face != TOP_FACE)
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
            return true; // At least one element
        }
    }
    return false;
}

bool View::element_is_above_span(const Element* e, Float3 pos, int span, int orientation) const
{
    if (e->pos().v2 <= pos.v2)
        return false;
    if (orientation == 0 || orientation == 2) { // cases 2 and 3
        float width = span + 1;
        float span_xlo = pos.v1 - width / 2 + 1;
        float span_xhi = pos.v1 + width / 2 - 1;
        float span_z = pos.v3;
        if (e->orientation() == 0 || e->orientation() == 2) {  // case 3
            float ewidth = e->width();
            float e_xlo = e->pos().v1 - ewidth / 2;
            float e_xhi = e->pos().v1 + ewidth / 2;
            float e_z = e->pos().v3;
            return (e_z == span_z) && (span_xhi >= e_xlo && span_xlo <= e_xhi);
        } else {                                              // case 2
            float ewidth = e->width();
            float e_zlo = e->pos().v3 - ewidth / 2;
            float e_zhi = e->pos().v3 + ewidth / 2;
            float e_x = e->pos().v1;
            return (e_zlo <= span_z && e_zhi >= span_z) && (span_xlo <= e_x && span_xhi >= e_x);
        }
    } else {                                    // cases 1 and 4
        float width = span + 1;
        float span_zlo = pos.v3 - width / 2 + 1;
        float span_zhi = pos.v3 + width / 2 - 1;
        float span_x = pos.v1;
        if (e->orientation() == 0 || e->orientation() == 2) {  // case 1
            float ewidth = e->width();
            float e_xlo = e->pos().v1 - ewidth / 2;
            float e_xhi = e->pos().v1 + ewidth / 2;
            float e_z = e->pos().v3;
            return (span_zlo <= e_z && span_zhi >= e_z) && (e_xlo <= span_x && e_xhi >= span_x);
        } else {                                              // case 4
            float ewidth = e->width();
            float e_zlo = e->pos().v3 - ewidth / 2;
            float e_zhi = e->pos().v3 + ewidth / 2;
            float e_x = e->pos().v1;
            return (e_x == span_x) && (span_zhi >= e_zlo && span_zlo <= e_zhi);
        }
    }
    return false;
}

int View::span_clearance(Float3 pos, int span, int orientation) const // return 0 means infinite clearance
{
    if (span < 1)
        return 0;
    float min_height = 0.0;
    for (int i = 0; i < m_doc->elements(); i++) {
        const Element* e = m_doc->element(i);
        if (!e->removed()) {
            if (e->kind() == ELEMENT_LEDGE) {
                if (element_is_above_span(e, pos, span, orientation)) {
                    if (min_height == 0.0)
                        min_height = e->pos().v2;
                    else
                        min_height = fmin(e->pos().v2, min_height);
                }
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

Vmenu& View::get_vmenu()
{
    return m_vmenu;
}

void View::set_mag(float mag)
{
    m_mag = fmax(1.0, mag);
    m_mag = fmin(10.0, m_mag);
    m_vmenu.set_mag(1.0 / m_mag);
    resize_calc();
}
