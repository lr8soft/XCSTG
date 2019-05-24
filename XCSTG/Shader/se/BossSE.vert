#version 330 core
uniform mat4 transform_mat;
layout (location=0) in vec4 in_coord;
void main(){
    gl_Position=transform_mat*in_coord;
}