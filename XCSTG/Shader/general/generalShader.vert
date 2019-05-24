#version 330 core
layout (location=0) in vec4 render_pos;
layout (location=1) in vec2 tex_pos;
uniform mat4 convert_mat;
out vec2 tex_coord;
void main(){
    gl_Position=convert_mat*render_pos;
    tex_coord=tex_pos;
}