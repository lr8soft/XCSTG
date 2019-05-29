#version 330 core
uniform mat4 transform_mat;
uniform float rand;
layout (location=0) in vec4 display_coord;
out vec4 color;
void main(){
    gl_Position=transform_mat*display_coord;
    gl_PointSize=50.0f;
    color=vec4(abs(sin(rand)),abs(cos(rand)),0.0,0.0);
}