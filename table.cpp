//
// table.cpp
//
#include "table.h"
#include "cad_model.h"

#include <QMouseEvent>
#include <QTime>

#include <cmath>

Table::Table(int& view_ix, QMatrix4x4& mvp_matrix, QMatrix4x4& rot_matrix, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_ms_at_start(QTime::currentTime().msecsSinceStartOfDay())
    , m_xrot(0.0)
    , m_yrot(0.0)
    , m_aspect(1.0)
    , m_fov(45.0)
    , m_camz(8.0)
    , m_marker_flag(false)
    , m_marker_pos({0.0, 0.0, 0.0})
    , m_width((512 * 1920) / 1080)
    , m_height(512)
    , m_thingy(NULL)
    , m_view_ix(view_ix)
    , m_mvp_matrix(mvp_matrix)
    , m_rot_matrix(rot_matrix)
{
    m_xrot = 0.0;
    setMinimumWidth(600);
    setMinimumHeight(337);
    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
    QString file_name = "house.txt";
    if (!m_doc.load_from_file(file_name)) {
        printf("Error loading doc: '%s'\n", m_doc.error_message().toLatin1().data());
    } else {
        printf("Loaded doc\n");
    }
    m_history.execute(new AddBrickCommand(QString("First one")));
    m_history.execute(new AddBrickCommand(QString("Second one")));
    m_history.execute(new AddBrickCommand(QString("Third one")));
    m_history.execute(new AddBrickCommand(QString("Fourth one")));
    m_history.execute(new AddBrickCommand(QString("Fifth one")));
}

Table::~Table()
{
    makeCurrent();
    delete m_thingy;
    doneCurrent();
}

void Table::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_thingy = new Thingus(m_doc);
    resize_calc();
    timer.start(33, this);
}

void Table::resize_calc()
{
    float znear = m_camz;
    float zfar = (m_thingy == NULL) ? m_camz * 4.0 : m_camz + 2.0 * m_thingy->radius();
    m_projection.setToIdentity();
    m_projection.perspective(m_fov, m_aspect, znear, zfar);
}


void Table::resizeGL(int w, int h)
{
    m_width = w;
    m_height = h;
    float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
    m_camz = (m_thingy == NULL) ? 2.0 / q : m_thingy->radius() / q;
    m_camz -= (m_thingy == NULL) ? 2.0 : m_thingy->radius();
    m_camz = 2.0 * m_camz / 3.0;
    m_aspect = qreal(w) / qreal(h ? h : 1);
    resize_calc();
}

void Table::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QVector3D axis1 = {1.0, 0.0, 0.0};
    QQuaternion rot1 = QQuaternion::fromAxisAndAngle(axis1, m_xrot);
    QVector3D axis2 = {0.0, 1.0, 0.0};
    QQuaternion rot2 = QQuaternion::fromAxisAndAngle(axis2, m_yrot);
    QQuaternion my_rot = rot1 * rot2;

    QMatrix4x4 matrix;
    float radius = (m_thingy == NULL) ? 2.0 : m_thingy->radius();
    float3 center = (m_thingy == NULL) ? float3{0.0, 0.0, 0.0} : m_thingy->center();
    matrix.translate(0.0, 0.0, -m_camz - radius);
    matrix.rotate(my_rot);
    matrix.translate(-center.v1, -center.v2, -center.v3);
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
        marker_matrix.translate(0.0, 0.0, 0.0);
    }
    m_program.setUniformValue("marker_matrix", marker_matrix);

    // Draw cube geometry
    m_thingy->drawCubeGeometry(&m_program);
}

void Table::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    if (!m_program.link())
        close();
    if (!m_program.bind())
        close();
}

void Table::timerEvent(QTimerEvent *)
{
    if (isVisible()) {
//        update();
    }
}

void Table::keyPressEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    bool shifted = (e->modifiers() & Qt::ShiftModifier) ? true : false;
    if (a == 0x6f) { // up
        m_xrot -= shifted ? 1.0 : 10.0;
        update();
    } else if (a == 0x74) { // down
        m_xrot += shifted ? 1.0 : 10.0;
        update();
    } else if (a == 0x71) { // left
        m_yrot -= shifted ? 1.0 : 10.0;
        update();
    } else if (a == 0x72) { // right
        m_yrot += shifted ? 1.0 : 10.0;
        update();
    } else if (a == 0x1f) { // i or I
        m_camz *= shifted ? (29.0 / 30.0) : (2.0 / 3.0);
        resize_calc();
        update();
    } else if (a == 0x20) { // o or O
        m_camz *= shifted ? (30.0 / 29.0) : (3.0 / 2.0);
        resize_calc();
        update();
    } else if (a == 0x2b) { // h or H
        float q = tan(m_fov * (3.1415927 / 180.0) / 2.0);
        m_camz = (m_thingy == NULL) ? 2.0 / q : m_thingy->radius() / q;
        m_camz -= (m_thingy == NULL) ? 2.0 : m_thingy->radius();
        m_camz = 2.0 * m_camz / 3.0;
        if (shifted) {
            m_xrot = 0.0;
            m_yrot = 0.0;
        }
        resize_calc();
        update();
    } else if (a == 0x1e) { // u or U
        if (m_history.can_undo())
            m_history.undo();
        else
            printf("At first command\n");
    } else if (a == 0x1b) { // r or R
        if (m_history.can_redo())
            m_history.redo();
        else
            printf("At last command\n");
    } else if (a == 0x36) { // c or C
        m_history.execute(new AddBrickCommand(QString("Keyboard command")));
    }
    QOpenGLWidget::keyPressEvent(e);
}

void Table::keyReleaseEvent(QKeyEvent* e)
{
    unsigned int a = e->nativeScanCode();
    if (a == 0x32) {
    } else if (a == 0x3e) {
    }
    QOpenGLWidget::keyReleaseEvent(e);
}

void Table::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        select_brick(e->pos().x(), e->pos().y());
    } else if (e->button() == Qt::RightButton) {
    }
    QOpenGLWidget::mousePressEvent(e);
}

void Table::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
    } else if (e->button() == Qt::RightButton) {
    }
    QOpenGLWidget::mouseReleaseEvent(e);
}

QPoint Table::w2s(const QVector3D point) const
{
    QVector4D sp = m_mvp_matrix * QVector4D(point, 1.0);
    QPoint res(m_width / 2 + round((sp.x() * (float) m_width) / (2.0 * sp.w())),
               m_height / 2 - round((sp.y() * (float) m_height) / (2.0 * sp.w())));
    return res;
}

float Table::distance(float3 pos1, float3 pos2) const
{
    return sqrt((pos1.v1 - pos2.v1) * (pos1.v1 - pos2.v1)
              + (pos1.v2 - pos2.v2) * (pos1.v2 - pos2.v2)
              + (pos1.v3 - pos2.v3) * (pos1.v3 - pos2.v3));

}

void Table::select_brick(int x, int y)
{
//    printf("Mouse position (%d, %d)\n", x, y);
    printf("try:\n");
    float max_level = -1.0;
    float3 sel_pos = {0.0, 0.0, 0.0};
    for (int i = 0; i < m_doc.elements(); i++) {
        Element* e = m_doc.get_element(i);
        Face tf = e->top_face();
        if (inside_face(tf, x, y)) {
//            printf("   Inside Element #%d  level = %f\n", i, e->top_level());
            for (int j = 0; j < e->sub_face_count(); j++) {
                Face sf = e->top_sub_face(j);
                if (inside_face(sf, x, y)) {
                    if (e->top_level() > max_level) {
                        max_level = e->top_level();
                        sel_pos.v1 = (sf.v1.v1 + sf.v3.v1) / 2.0;
                        sel_pos.v2 = e->top_level();
                        sel_pos.v3 = (sf.v1.v3 + sf.v3.v3) / 2.0;
//                        printf("   Subface center (%f, %f, %f)\n", sel_pos.v1, sel_pos.v2, sel_pos.v3);
                    }
                }
            }
        }
    }
    bool occupied = false;
    if (max_level >= 0.0) {
        sel_pos.v2 += 0.5;
//        printf("Position Selected: (%f, %f, %f)\n", sel_pos.v1, sel_pos.v2, sel_pos.v3);
        for (int i = 0; i < m_doc.elements(); i++) {
            Element* e = m_doc.get_element(i);
            if (e->contains(sel_pos)) {
                occupied = true;
            }
        }
        if (!occupied) {
            if (m_marker_flag) {
                if (distance(m_marker_pos, sel_pos) < 0.1) {
                    m_marker_flag = false;
                    m_marker_pos = {0.0, 0.0, 0.0};
                } else if (distance(m_marker_pos, sel_pos) == 1.0 && m_marker_pos.v2 == sel_pos.v2) {
                    printf("add brick\n");
                    m_marker_pos = {0.0, 0.0, 0.0};
                    m_marker_flag = false;
                } else {
                    m_marker_pos = sel_pos;
                    m_marker_flag = true;
                }
            } else {
                m_marker_pos = sel_pos;
                m_marker_flag = true;
//                printf("Finally a location: (%f, %f, %f)\n", sel_pos.v1, sel_pos.v2, sel_pos.v3);
            }
            update();
        }
    }
}

bool Table::inside_face(const Face& f, int sx, int sy)
{
    // transform the four vertices of f
    // perform the four cross products in counter clockwise order
    QPoint a = w2s(QVector3D(f.v1.v1, f.v1.v2, f.v1.v3));
    QPoint b = w2s(QVector3D(f.v2.v1, f.v2.v2, f.v2.v3));
    QPoint c = w2s(QVector3D(f.v3.v1, f.v3.v2, f.v3.v3));
    QPoint d = w2s(QVector3D(f.v4.v1, f.v4.v2, f.v4.v3));
    int ca = zcross(a, b, sx, sy);
    int cb = zcross(b, c, sx, sy);
    int cc = zcross(c, d, sx, sy);
    int cd = zcross(d, a, sx, sy);
    return (ca < 0 && cb < 0 && cc < 0 && cd < 0);
}

int Table::zcross(const QPoint& a, const QPoint& b, int sx, int sy) const
{
    int ax = a.x() - sx;
    int ay = a.y() - sy;
    int bx = b.x() - sx;
    int by = b.y() - sy;
    return ax * by - bx * ay;
}
