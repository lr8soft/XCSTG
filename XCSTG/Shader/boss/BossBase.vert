#version 330 core
uniform mat4 transform_mat;
in vec4 display_coord;
in vec2 input_tex_coord;
out vec2 tex_coord;
void main(){
    gl_Position=transform_mat*display_coord;
    tex_coord=input_tex_coord;
}