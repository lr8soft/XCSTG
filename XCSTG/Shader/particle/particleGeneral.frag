#version 330 core
uniform sampler2D tex;
in vec2 middle_tex_coord;
out vec4 out_frag;
void main(){
    out_frag=texture(tex,gl_PointCoord);
}