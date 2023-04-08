#include "view.h"
#include "matrix4x4.h"
#include "matrix3x3.h"
#include "paint_can.h"
#include "track.h"
#include "section.h"
#include "cube_shape.h"
#include "bounding_box.h"
#include "look.h"
#include "pi.h"
#include <math.h>
#include <sys/stat.h>
#include <algorithm>
#include <stdio.h>

#define notVERBOSE
#define TRACK_LANES 4

View::View(SDL_Window* window)
    : m_window(window)
    , m_renderer(nullptr)
    , m_context(nullptr)
    , m_program(0)
    , m_pos_attr(0)
    , m_col_attr(0)
    , m_norm_attr(0)
    , m_ani_attr(0)
    , m_mvp_matrix_uniform(0)
    , m_rot_matrix_uniform(0)
    , m_car0_matrix_uniform(0)
    , m_car1_matrix_uniform(0)
    , m_car2_matrix_uniform(0)
    , m_car3_matrix_uniform(0)
    , m_vbo(0)
    , m_qa(new Qa)
    , m_frame(0)
    , m_max_vertex_count(1024 * 1024)
    , m_aux_count(0)
    , m_aux_model(new CadModel())
    , m_change(true)
    , m_radius(2.0)
    , m_center({0.0, 0.0, 0.0})
    , m_width(INITIAL_WIDTH)
    , m_height(INITIAL_HEIGHT)
    , m_aspect(1.0)
    , m_mag(INITIAL_MAG)
    , m_fov(45.0)
    , m_camz(8.0)
    , m_xrot(INITIAL_XROT)
    , m_yrot(0.0)
    , m_xoff(0.0)
    , m_yoff(0.0)
    , m_track(new Track(TRACK_LANES))
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video Initialization Error: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        printf("Context Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == NULL) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    build_track();
    decorate_model();
    m_change = false;
}

void View::build_track()
{
    for (int i = 0; i < m_track->sections(); i++) {
        CadModel cm = m_track->section(i)->cad_model();
        m_aux_model->add(cm, 0.0, 0.0, 0.0);
    }
    for (int i = 0; i < m_track->cars(); i++) {
        m_track->car(i)->set_lane(i);
        CadModel car = m_track->car(i)->cad_model(i);
        m_aux_model->add(car, 0.0, 0.0, 0.0);
    }
}

void View::decorate_model()
{
    BoundingBox bb = m_aux_model->bounding_box();
    float tablex = bb.vmax.v1 - bb.vmin.v1 + 4.0;
    float tabley = Look::dimh / 20.0;
    float tablez = bb.vmax.v3 - bb.vmin.v3 + 4.0;
    CubeShape table(tablex, tabley, tablez);
    CadModel tt(table, Look::table_paint(), 1.0);

    bb.vmin.v1 -= 2.0;
    bb.vmin.v3 -= 2.0;
    bb.vmax.v1 += 2.0;
    bb.vmax.v3 += 2.0;

    m_radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    m_radius = fmax(m_radius, (bb.vmax.v2 - bb.vmin.v2) / (2.0));
    m_radius = fmax(m_radius, 2.0);
    m_radius *= sqrt(2.0);
    m_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
//    printf("m_radius = %5.2f, center = (%5.2f, %5.2f, %5.2f)\n", m_radius, m_center.v1, m_center.v2, m_center.v3);
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
    delete m_qa;
    delete m_track;
    delete m_aux_model;
    SDL_DestroyRenderer(m_renderer);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

bool View::add_shader_from_source_file(GLuint shader, const char* name)
{
    FILE* fin = fopen(name, "r");
    if (fin == NULL) {
        printf("add_shader_from_source_file(%s): File not found\n", name);
        return false;
    }
    struct stat st;
    stat(name, &st);
    int file_size = st.st_size;
    if (file_size <= 0) {
        printf("add_shader_from_source_file(%s): File empty\n", name);
        return false;
    }
    GLchar* src_buffer[1];
    src_buffer[0] = new GLchar[file_size + 1];
    int res = fread(src_buffer[0], 1, file_size, fin);
    if (res != file_size) {
        printf("add_shader_from_source_file(%s): Error reading file\n", name);
        return false;
    }
    fclose(fin);
    GLchar* ptr = src_buffer[0];
    ptr[file_size] = 0;
    glShaderSource(shader, 1, src_buffer, NULL);
    delete [] src_buffer[0];
    glCompileShader(shader);
    GLint shader_compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE) {
        printf("add_shader_from_source_file(%s): Unable to compile file\n", name);
        print_shader_log(shader);
        return false;
    }
    return true;
}

void View::initialize()
{
#ifdef VERBOSE
    printf("View::initialize()\n");
#endif
    const char* vshader_name = "vshader.glsl";
    const char* fshader_name = "fshader.glsl";
    GLuint vshader = 0;
    GLuint fshader = 0;
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        printf("Error initializing GLEW: %s\n", glewGetErrorString(glew_error));
        exit(0);
    }
    if (SDL_GL_SetSwapInterval(2) < 0) {
        printf("Warning: Unable to set VSync. SDL Error: %s\n", SDL_GetError());
    }
    glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_program = glCreateProgram();
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!add_shader_from_source_file(vshader, vshader_name)) {
        printf("Error loading vertex shader source '%s'\n", vshader_name);
        exit(0);
    }
    glAttachShader(m_program, vshader);
    if (!add_shader_from_source_file(fshader, fshader_name)) {
        printf("Error loading fragment shader source '%s'\n", fshader_name);
        exit(0);
    }
    glAttachShader(m_program, fshader);
    glLinkProgram(m_program);
    GLint program_success = GL_TRUE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &program_success);
    if (program_success != GL_TRUE) {
        printf("Error ilinking program\n");
        exit(0);
    }
    m_pos_attr = glGetAttribLocation(m_program, "a_position");
    if (m_pos_attr == -1) {
        printf("a_position is not a valid glsl variable\n");
        exit(0);
    }
    m_col_attr = glGetAttribLocation(m_program, "a_color");
    if (m_col_attr == -1) {
        printf("a_color is not a valid glsl variable\n");
        exit(0);
    }
    m_norm_attr = glGetAttribLocation(m_program, "a_normal");
    if (m_norm_attr == -1) {
        printf("a_normal is not a valid glsl variable\n");
        exit(0);
    }
    m_ani_attr = glGetAttribLocation(m_program, "a_animation_id");
    if (m_ani_attr == -1) {
        printf("a_animation_id is not a valid glsl variable\n");
        exit(0);
    }
    m_mvp_matrix_uniform = glGetUniformLocation(m_program, "mvp_matrix");
    if (m_mvp_matrix_uniform == -1) {
        printf("mvp_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_rot_matrix_uniform = glGetUniformLocation(m_program, "rot_matrix");
    if (m_rot_matrix_uniform == -1) {
        printf("rot_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_car0_matrix_uniform = glGetUniformLocation(m_program, "car0_matrix");
    if (m_car0_matrix_uniform == -1) {
        printf("car0_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_car1_matrix_uniform = glGetUniformLocation(m_program, "car1_matrix");
    if (m_car1_matrix_uniform == -1) {
        printf("car1_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_car2_matrix_uniform = glGetUniformLocation(m_program, "car2_matrix");
    if (m_car2_matrix_uniform == -1) {
        printf("car2_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_car3_matrix_uniform = glGetUniformLocation(m_program, "car3_matrix");
    if (m_car3_matrix_uniform == -1) {
        printf("car3_matrix is not a valid glsl variable\n");
        exit(0);
    }
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    copy_aux_facets();
}

void View::sub_copy_facets(CadModel* model, VertexData* vertices, int& vix)
{
    float an_id;
    Float3 vp, vc, vn;
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        vc = model->facet_color(i);
        vn = model->facet_normal(i);
        vp = model->facet_v1(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
        vp = model->facet_v2(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
        vp = model->facet_v3(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
    }
}

void View::copy_aux_facets()
{
    m_aux_count = 3 * m_aux_model->facets();
    if (m_aux_count > 0) {
        VertexData* vertices = new VertexData[m_aux_count];
        int vix = 0;
        sub_copy_facets(m_aux_model, vertices, vix);
        // Transfer vertex data to VBO
        glBufferData(GL_ARRAY_BUFFER, m_aux_count * sizeof(VertexData), vertices, GL_STATIC_DRAW);
        delete [] vertices;
    }
}

void View::resize(int w, int h)
{
#ifdef VERBOSE
    printf("View::resize(%d, %d)\n", w, h);
#endif
    m_width = w;
    m_height = h;
    m_aspect = float(m_width) / float(m_height ? m_height : 1.0);
    glViewport(0, 0, m_width, m_height);
    resize_calc();
}

void View::resize_calc()
{
    float q = tan(m_fov * (PI / 180.0) / 2.0);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    float znear = 0.1;
    float zfar = m_camz + 2.0 * m_radius;
    m_projection.perspective(m_fov / m_mag, m_aspect, znear, zfar);
//    printf("m_fov = %5.3f, m_mag = %5.3f, m_aspect = %5.2f, znear = %5.2f, zfar = %5.2f\n", m_fov, m_mag, m_aspect, znear, zfar);
}

void View::check_storage()
{
    int fc = 3 * m_aux_model->facets();
    if (m_max_vertex_count > fc)
        return;
    m_max_vertex_count = std::max(2 * m_max_vertex_count, 2 * fc);
}

void View::render()
{
#ifdef VERBOSE
    printf("View::render()\n");
#endif
//    if (m_change) {
//        decorate_model();
//        resize_calc();
//        check_storage();
//        copy_aux_facets();
//        m_change = false;
//    }

    m_qa->add_sample(QA_START_RENDER, SDL_GetPerformanceCounter(), m_frame);

//    int tp = duration_cast<nanoseconds>(total_period).count();
    int tp = (33333333 * 3) / 2;

    m_track->advance(tp);

    Matrix4x4 matrix;
    matrix.unity();
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.rotate_ax(m_xrot);
    matrix.rotate_ay(m_yrot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;

    m_qa->add_sample(QA_BEFORE_CLEAR, SDL_GetPerformanceCounter(), m_frame);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_qa->add_sample(QA_AFTER_CLEAR, SDL_GetPerformanceCounter(), m_frame);

    glUseProgram(m_program);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(m_pos_attr);
    glEnableVertexAttribArray(m_col_attr);
    glEnableVertexAttribArray(m_norm_attr);
    glEnableVertexAttribArray(m_ani_attr);

    int stride = sizeof(VertexData);
    char* offset = 0;
    glVertexAttribPointer(m_pos_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_norm_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_col_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_ani_attr, 1, GL_FLOAT, GL_FALSE, stride, (void*) offset);

    glUniformMatrix4fv(m_mvp_matrix_uniform, 1, GL_TRUE, m_mvp_matrix.data());
    glUniformMatrix4fv(m_rot_matrix_uniform, 1, GL_TRUE, m_rot_matrix.data());
    if (m_track->cars() > 0) {
        int car_id = 0;
        Matrix4x4 car_matrix;
        Double3 cp = m_track->car_position(car_id);
        car_matrix.unity();
        car_matrix.translate(cp.v1, cp.v2, cp.v3);
        car_matrix.rotate_ay(m_track->car_yaw(car_id));
        car_matrix.rotate_az(m_track->car_pitch(car_id));
        glUniformMatrix4fv(m_car0_matrix_uniform, 1, GL_TRUE, car_matrix.data());
    }
    if (m_track->cars() > 1) {
        int car_id = 1;
        Matrix4x4 car_matrix;
        Double3 cp = m_track->car_position(car_id);
        car_matrix.unity();
        car_matrix.translate(cp.v1, cp.v2, cp.v3);
        car_matrix.rotate_ay(m_track->car_yaw(car_id));
        car_matrix.rotate_az(m_track->car_pitch(car_id));
        glUniformMatrix4fv(m_car1_matrix_uniform, 1, GL_TRUE, car_matrix.data());
    }
    if (m_track->cars() > 2) {
        int car_id = 2;
        Matrix4x4 car_matrix;
        Double3 cp = m_track->car_position(car_id);
        car_matrix.unity();
        car_matrix.translate(cp.v1, cp.v2, cp.v3);
        car_matrix.rotate_ay(m_track->car_yaw(car_id));
        car_matrix.rotate_az(m_track->car_pitch(car_id));
        glUniformMatrix4fv(m_car2_matrix_uniform, 1, GL_TRUE, car_matrix.data());
    }
    if (m_track->cars() > 3) {
        int car_id = 3;
        Matrix4x4 car_matrix;
        Double3 cp = m_track->car_position(car_id);
        car_matrix.unity();
        car_matrix.translate(cp.v1, cp.v2, cp.v3);
        car_matrix.rotate_ay(m_track->car_yaw(car_id));
        car_matrix.rotate_az(m_track->car_pitch(car_id));
        glUniformMatrix4fv(m_car3_matrix_uniform, 1, GL_TRUE, car_matrix.data());
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, m_aux_count);

    glDisableVertexAttribArray(m_ani_attr);
    glDisableVertexAttribArray(m_norm_attr);
    glDisableVertexAttribArray(m_col_attr);
    glDisableVertexAttribArray(m_pos_attr);
    glUseProgram(0);
    m_qa->add_sample(QA_AFTER_SWAP_BUFFERS, SDL_GetPerformanceCounter(), m_frame);
    SDL_GL_SwapWindow(m_window);
    m_qa->add_sample(QA_AFTER_SWAP_BUFFERS, SDL_GetPerformanceCounter(), m_frame);
    glFinish();
    m_qa->add_sample(QA_AFTER_FINISH, SDL_GetPerformanceCounter(), m_frame);
    ++m_frame;
}

void View::translate_x(int x)
{
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wx = m_aspect * (m_camz + m_radius) * q;
    float ratio = (float) x / fmax(1.0, (float) m_width);
    float dx = wx * ratio;
    m_xoff += (      dx        );
}

void View::translate_y(int y)
{
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wy = (m_camz + m_radius) * q;
    float ratio = (float) y / fmax(1.0, (float) m_height);
    float dy = wy * ratio;
    m_yoff -= (      dy        );
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
    m_xrot = INITIAL_XROT;
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

void View::set_mag(float mag)
{
    m_mag = fmax(1.0, mag);
    m_mag = fmin(10.0, m_mag);
    resize_calc();
}

int View::width() const
{
    return m_width;
}

int View::height() const
{
    return m_height;
}

void View::print_program_log(GLuint program)
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void View::print_shader_log(GLuint shader)
{
   //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}
