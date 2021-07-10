#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;
uniform float ani_sel1;
uniform mat4 ani_matrix1;
uniform mat4 ani_matrix2;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec3 a_color;
attribute float a_animation_id;

varying vec4 v_normal;
varying vec3 v_color;

void main()
{
    vec3 billy;
    billy = normalize(a_normal);

// Calculate vertex position in screen space
    gl_Position = mvp_matrix * vec4(ani_sel1 * a_position, 1.0);
    v_normal = rot_matrix * vec4(billy, 0.0);
    // Pass color coordinate to fragment shader
    v_color = a_color;
}
