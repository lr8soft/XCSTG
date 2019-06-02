#version 330 core
in vec2 tex_coord;
out vec4 draw_vec4;
uniform sampler2D tex;
uniform vec4 font_color;
void main(){
    vec2 tex_coord=gl_PointCoord;
    vec4 temp_frag=texture(tex,tex_coord);
    draw_vec4=temp_frag*font_color;
}