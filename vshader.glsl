#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;
uniform mat4 car_matrix;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec3 a_color;
attribute float a_animation_id;

varying vec4 v_normal;
varying vec4 v_color;

void main()
{
    vec3 billy;
    billy = normalize(a_normal);

// Calculate vertex position in screen space
    if (a_animation_id == 0.0) { // Optimize this most common case
        gl_Position = mvp_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * vec4(billy, 0.0);
    } else {
        if (a_animation_id == 2.0) {
            gl_Position = mvp_matrix * car_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * car_matrix * vec4(billy, 0.0);
        } else if (a_animation_id == 1.0) {
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
        } else { // Treat unknowns like 0.0
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * vec4(billy, 0.0);
        }
    }
    // Pass color coordinate to fragment shader
    v_color = vec4(a_color, 1.0);
}
