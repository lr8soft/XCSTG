#version 330 core
uniform sampler2D tex;
uniform float rand;
in vec4 color;
void main(){
    vec2 tex_coord=gl_PointCoord;
    gl_FragColor = texture2D(tex,tex_coord);//;
}