#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

varying vec4 v_normal;
varying vec3 v_color;

void main()
{
    float c = abs(v_normal.z);
    vec3 billy;
    billy.r = c * v_color.r;
    billy.g = c * v_color.g;
    billy.b = c * v_color.b;
    gl_FragColor = vec4(billy, 1.0);
}

