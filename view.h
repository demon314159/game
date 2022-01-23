
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
    int mouse_delete(int sx, int sy);
    void mouse_unselect();
    bool new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool &roof);
    bool gap_below_span(Float3 pos, int span, int orientation) const;
    bool span_blocked(Float3 pos, int span, int orientation) const;
    bool element_is_above_span(const Element* e, Float3 pos, int span, int orientation) const;
    int span_clearance(Float3 pos, int span, int orientation) const;
    int force_vmenu_item_chosen(int sx, int sy);
    Vmenu& get_force_vmenu();
    int edit_vmenu_item_chosen(int sx, int sy);
    Vmenu& get_edit_vmenu();

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void check_storage();
    void copy_facets();
    void render_facets();
    bool top_face_covered(const Element* e) const;
    bool top_subface_covered(const Element* e, int ix) const;
    int selected_element_ix(int sx, int sy) const;
    int selected_top_subface(const Element* e, int sx, int sy) const;
    bool no_part_of_any_element_selected(int sx, int sy) const;
    Float2 world2screen(Float3 point) const;
    bool screen_point_inside_face(const Face& f, int sx, int sy) const;
    Float3 screen_point_on_floor(const Face& f, int sx, int sy) const;
    float min4(float a, float b, float c, float d) const;
    float max4(float a, float b, float c, float d) const;
    double len(Float2 v1, Float2 v2) const;
    double tri_area(Float2 v1, Float2 v2, Float2 v3) const;
    double quad_area(Float2 v1, Float2 v2, Float2 v3, Float2 v4) const;
    float normalize_angle(float angle) const;

private:
    Vmenu m_force_vmenu;
    Vmenu m_edit_vmenu;
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
    float m_xrot;
    float m_yrot;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    QMatrix4x4 m_projection;
};

#endif // _VIEW_H_
