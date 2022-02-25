
#ifndef _VIEW_H_
#define _VIEW_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "document.h"
#include "cad_model.h"
#include "document.h"
#include "choose.h"
#include "vmenu.h"
#include "mouse_vector.h"

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    float animation_id;
};

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
    void translate_x(float dx);
    void translate_y(float dy);
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void rotate_home();
    void zoom(float factor);
    void zoom_home();
    void translate_x(int x);
    void translate_y(int y);
    void translate_home();
    bool mouse_select(int sx, int sy);
    int mouse_delete(int sx, int sy);
    void mouse_unselect();
    MouseVector new_mouse_vector(int sx, int sy) const;
    bool mouse_vector_intersects(const MouseVector& mv, const Element* e) const;
    bool new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool &roof);
    bool gap_below_span(Float3 pos, int span, int orientation) const;
    bool span_blocked(Float3 pos, int span, int orientation) const;
    bool element_is_above_span(const Element* e, Float3 pos, int span, int orientation) const;
    int span_clearance(Float3 pos, int span, int orientation) const;
    int vmenu_item_chosen(int sx, int sy);
    Vmenu& get_vmenu();

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void check_storage();
    void copy_facets();
    void sub_copy_facets(VertexData* vertices, int& vix, bool transparent);
    void render_facets();
    bool top_face_covered(const Element* e) const;
    bool top_subface_covered(const Element* e, int ix) const;
    int selected_element_ix(int sx, int sy, const MouseVector& mv) const;
    int selected_top_subface(const Element* e, int sx, int sy) const;
    bool no_part_of_any_element_selected(int sx, int sy, const MouseVector& mv) const;
    Float2 world2screen(Float3 point, float* distance = NULL) const;
    Float2 fixed2screen(Float3 point) const;
    bool screen_point_inside_face(const Face& f, int sx, int sy, float* depth = NULL) const;
    bool screen_point_inside_fixed_face(const Face& f, int sx, int sy) const;
    Float3 screen_point_on_floor(const Face& f, int sx, int sy) const;
    float min4(float a, float b, float c, float d) const;
    float max4(float a, float b, float c, float d) const;
    double len(Float2 v1, Float2 v2) const;
    double tri_area(Float2 v1, Float2 v2, Float2 v3) const;
    double quad_area(Float2 v1, Float2 v2, Float2 v3, Float2 v4) const;
    float normalize_angle(float angle) const;
    void add_grid(CadModel* cm, const BoundingBox& bb);

private:
    MouseVector m_mouse_vector;
    Vmenu m_vmenu;
    Choose m_choose;
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
    float m_zoom;
    float m_xrot;
    float m_yrot;
    float m_xoff;
    float m_yoff;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_fixed_matrix;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    QMatrix4x4 m_projection;
};

#endif // _VIEW_H_
