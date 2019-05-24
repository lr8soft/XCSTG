#version 330 core
in vec2 tex_pos;
out vec4 o_color;
uniform sampler2D tex;
void main(){
    o_color=texture(tex,tex_pos);
}