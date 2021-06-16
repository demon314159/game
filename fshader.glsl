#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

varying vec4 v_normal;
varying vec3 v_color;

void main()
{
    float c = abs(v_normal.z) / 2.0;
    vec3 billy;
    billy.x = c * v_color.x;
    billy.y = c * v_color.y;
    billy.z = c * v_color.z;
    gl_FragColor = vec4(billy, 1.0);
}

