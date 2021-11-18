
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
    bool initialize();
    void resize(int w, int h);
    void paint();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void rotate_home();
    void zoom(float factor);
    void zoom_home();

protected:
    bool init_shaders();
    void resize_calc();
    void decorate_model();
    void copy_facets();
    void render_facets();

private:
    int m_max_vertices;
    int m_vertices;
    Document* m_doc;
    CadModel* m_model;
    QOpenGLBuffer m_vertex_buf;
    float m_radius;
    float3 m_center;
    int m_width;
    int m_height;
    float m_aspect;
    float m_fov;
    float m_camz;
    float m_xrot;
    float m_yrot;
    bool m_marker_flag;
    float3 m_marker_pos;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_mvp_matrix;
    QMatrix4x4 m_rot_matrix;
    QMatrix4x4 m_projection;
};

#endif // _VIEW_H_
