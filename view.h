
#ifndef _VIEW_H_
#define _VIEW_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "document.h"
#include "cad_model.h"
#include "document.h"

class View: protected QOpenGLFunctions
{
public:
    View(Document* doc);
    virtual ~View();
    Document* get_doc() const;
    Document* replace_doc(Document* doc);
    bool initialize();
    void resize(int w, int h);
    void paint();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void rotate_home();
    void zoom(float factor);
    void zoom_home();
    void mouse_select(int sx, int sy);

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void check_storage();
    void copy_facets();
    void render_facets();
    void clear_marker();
    int selected_element_ix(int sx, int sy);
    Float2 world2screen(Float3 point) const;
    bool screen_point_inside_face(const Face& f, int sx, int sy) const;
    int screen_cross_product(Float2 a, Float2 b, int sx, int sy) const;

private:
    int m_max_vertices;
    int m_vertices;
    Document* m_doc;
    CadModel* m_model;
    QOpenGLBuffer m_vertex_buf;
    float m_radius;
    Float3 m_center;
    int m_width;
    int m_height;
    float m_aspect;
    float m_fov;
    float m_camz;
    float m_xrot;
    float m_yrot;
    bool m_marker_flag;
    Float3 m_marker_pos;
    CadModel m_marker_model;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    QMatrix4x4 m_projection;
};

#endif // _VIEW_H_
