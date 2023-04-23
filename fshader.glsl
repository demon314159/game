varying vec4 v_normal;
varying vec4 v_color;

void main()
{
    float c = abs(v_normal.z);
    vec4 billy;
    billy.r = c * v_color.r;
    billy.g = c * v_color.g;
    billy.b = c * v_color.b;
    billy.a = v_color.a;
    gl_FragColor = billy;
}

