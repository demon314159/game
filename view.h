
#ifndef _VIEW_H_
#define _VIEW_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "vertex_data.h"
#include "track.h"
#include "cad_model.h"
#include "qa.h"
#include <chrono>

#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH ((INITIAL_HEIGHT * 1920) / 1080)
#define INITIAL_XROT 40.0
#define INITIAL_MAG 2.25

using namespace std::chrono;

class View: protected QOpenGLFunctions
{
public:
    View();
    virtual ~View();
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
    void set_mag(float mag);
    int width() const;
    int height() const;

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void check_storage();
//    void copy_vertices();
//    void copy_changed_vertices();
    void sub_copy_facets(CadModel* model, VertexData* vertices, int& vix);
    void copy_aux_facets();
    void render_facets();
    void build_track();

private:
    Qa* m_qa;
    int m_frame;
    high_resolution_clock::time_point m_time_at_start;
    int m_max_vertex_count;
    int m_aux_count;
    CadModel* m_aux_model;
    bool m_change;
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
    Track* m_track;
    QOpenGLBuffer m_vertex_buf;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    QMatrix4x4 m_projection;
};

#endif // _VIEW_H_
