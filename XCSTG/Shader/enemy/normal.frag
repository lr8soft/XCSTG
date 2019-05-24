#version 330 core
uniform sampler2D tex;
in vec2 tex_pos;
out vec4 draw_info;
void main(){
    draw_info=texture(tex,tex_pos);
}