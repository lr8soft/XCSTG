#version 330 core
uniform sampler2D tex;
in vec2 tex_coord;
out vec4 draw_frag;
void main(){
    draw_frag=texture(tex,tex_coord);
}