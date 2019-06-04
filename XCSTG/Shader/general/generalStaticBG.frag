#version 330 core
uniform sampler2D tex;
in vec2 Tex_coord;
out vec4 frag_color;
void main(){
    frag_color  =   texture(tex,Tex_coord);
}