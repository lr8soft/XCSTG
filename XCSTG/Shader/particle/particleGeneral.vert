#version 330 core
uniform mat4 transform_mat;
layout (location=0) in vec4 display_coord;
void main(){
    gl_Position=transform_mat*vec4(display_coord.xyz,1.0);
    gl_PointSize=display_coord.w;
}