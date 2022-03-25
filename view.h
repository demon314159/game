
#ifndef _VIEW_H_
#define _VIEW_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "document.h"
#include "vertex_image.h"
#include "cad_model.h"
#include "document.h"
#include "choose.h"
#include "vmenu.h"
#include "mouse_vector.h"

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
    void translate_x(int x);
    void translate_y(int y);
    void translate_home();
    bool mouse_select(int sx, int sy);
    int mouse_delete(int sx, int sy);
    void mouse_unselect();
    MouseVector new_mouse_vector(int sx, int sy) const;
    bool mouse_vector_intersects(const MouseVector& mv, const Face& f, float& depth) const;
    bool mouse_vector_intersects(const MouseVector& mv, const Element* e) const;
    bool new_element_chosen(Float3& pos, int& span, int& orientation, bool& same_level, bool &roof);
    bool gap_below_span(Float3 pos, int span, int orientation) const;
    bool span_blocked(Float3 pos, int span, int orientation) const;
    bool element_is_above_span(const Element* e, Float3 pos, int span, int orientation) const;
    int span_clearance(Float3 pos, int span, int orientation) const;
    int vmenu_item_chosen(int sx, int sy);
    Vmenu& get_vmenu();
    void set_mag(float mag);
    int width() const;
    int height() const;

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void check_storage();
    void copy_vertices();
    void copy_changed_vertices();
    void sub_copy_facets(CadModel* model, VertexData* vertices, int& vix, bool transparent);
    void copy_aux_facets();
    void render_facets();
    bool top_face_covered(const Element* e) const;
    bool top_subface_covered(const Element* e, int ix) const;
    int selected_element_ix(const MouseVector& mv) const;
    int selected_top_subface(const Element* e, int sx, int sy) const;
    bool no_part_of_any_element_selected(const MouseVector& mv) const;
    Float2 world2screen(Float3 point) const;
    Float2 fixed2screen(Float3 point) const;
    bool screen_point_inside_face(const Face& f, int sx, int sy) const;
    bool screen_point_inside_fixed_face(const Face& f, int sx, int sy) const;
    float min4(float a, float b, float c, float d) const;
    float max4(float a, float b, float c, float d) const;
    double len(Float2 v1, Float2 v2) const;
    double len(Float3 v1, Float3 v2) const;
    double tri_area(Float2 v1, Float2 v2, Float2 v3) const;
    double tri_area(Float3 v1, Float3 v2, Float3 v3) const;
    double quad_area(Float2 v1, Float2 v2, Float2 v3, Float2 v4) const;
    double quad_area(Float3 v1, Float3 v2, Float3 v3, Float3 v4) const;
    float normalize_angle(float angle) const;
    void add_grid(CadModel* cm, const BoundingBox& bb);
    Float3 normal(const Face& f) const;
    bool a_bit_less_than_all(float x, float x1, float x2, float x3, float x4) const;
    bool a_bit_more_than_all(float x, float x1, float x2, float x3, float x4) const;

    // this will change to return boolean
    float score(Float3 pt, Float3 pt1, Float3 pt2, Float3 pt3, Float3 pt4) const;

private:
    Vmenu m_vmenu;
    Choose m_choose;
    int m_max_vertex_count;
    int m_building_count;
    int m_glass_count;
    int m_aux_count;
    Document* m_doc;
    VertexImage m_building;
    VertexImage m_glass;
    CadModel* m_table;
    CadModel* m_aux_model;
    QOpenGLBuffer m_vertex_buf;
    float m_radius;
    Float3 m_center;
    int m_width;
    int m_height;
    float m_aspect;
    float m_mag;
    float m_fov;
    float m_camz;
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
