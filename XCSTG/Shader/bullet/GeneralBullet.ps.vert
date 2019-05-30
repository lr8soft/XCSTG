#version 330 core
layout (location=0) in vec4 in_coord;
uniform mat4 transform_mat;
uniform float point_size;
void main(){
    gl_Position=transform_mat*vec4(in_coord.xyz,1.0);
    gl_PointSize=point_size;//毕竟pointsize
}