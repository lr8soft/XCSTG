#version 330 core
uniform mat4 transform_mat;
layout (location=0) in vec4 display_coord;
layout (location=1) in vec2 input_tex_pos;
out vec4 middle_color;
out vec2 tex_pos;
void main(){
    gl_Position=transform_mat*display_coord;
    tex_pos=input_tex_pos;
}