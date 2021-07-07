#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;
uniform float ani_sel1;
uniform float ani_sel2;
uniform float ani_sel3;
uniform mat4 ani_matrix1;
uniform mat4 ani_matrix2;
uniform mat4 ani_matrix3;
uniform float left_digit;
uniform float middle_digit;
uniform float right_digit;
uniform float left_out;
uniform float middle_out;
uniform float right_out;
uniform mat4 digit_matrix;

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
    if (a_animation_id > 0.0 && a_animation_id == ani_sel1) {
        gl_Position = mvp_matrix *  ani_matrix1 * vec4(a_position, 1.0);
        v_normal = rot_matrix * ani_matrix1 * vec4(billy, 0.0);
    } else if (a_animation_id > 0.0 && a_animation_id == ani_sel2) {
        gl_Position = mvp_matrix *  ani_matrix2 * vec4(a_position, 1.0);
        v_normal = rot_matrix * ani_matrix2 * vec4(billy, 0.0);
    } else if (a_animation_id > 0.0 && a_animation_id == ani_sel3) {
        gl_Position = mvp_matrix *  ani_matrix3 * vec4(a_position, 1.0);
        v_normal = rot_matrix * ani_matrix3 * vec4(billy, 0.0);
    } else if (a_animation_id > 0.0 && (a_animation_id == left_digit || a_animation_id == middle_digit || a_animation_id == right_digit)) {
        gl_Position = mvp_matrix *  digit_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * digit_matrix * vec4(billy, 0.0);
    } else if (a_animation_id > 0.0 && (a_animation_id == left_out || a_animation_id == middle_out || a_animation_id == right_out)) {
        gl_Position = mvp_matrix *  digit_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * digit_matrix * vec4(billy, 0.0);
    } else {
        gl_Position = mvp_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * vec4(billy, 0.0);
    }
    // Pass color coordinate to fragment shader
    v_color = a_color;
}
