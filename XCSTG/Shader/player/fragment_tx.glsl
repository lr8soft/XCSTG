#version 330 core
uniform sampler2D tex;
in vec2 tex_pos;
out vec4 o_color;
void main(){
    o_color=texture(tex,tex_pos);
}