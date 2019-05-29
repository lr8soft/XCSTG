#version 330 core
uniform sampler2D tex;
uniform float time;
void main(){
    vec2 tex_coord=gl_PointCoord;
    vec2 calc_coord=gl_PointCoord-vec2(0.5);
    float dist = dot(calc_coord,calc_coord);
    if(dist>=0.25)
         discard;
    gl_FragColor = texture2D(tex,tex_coord)+vec4(abs(sin(time)),abs(cos(time)),abs(sin(time)+cos(time)),0.0);
}