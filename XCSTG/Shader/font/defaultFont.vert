#version 330 core
uniform mat4 convert_mat;
uniform int font_size;
layout (location=0) in vec4 draw_info;//position vec2,texture vec2
out vec2 tex_coord;
void main(){
    gl_Position=convert_mat*vec4(draw_info.xy,0.0,0.0);
    tex_coord=vec2(draw_info.zw);
    gl_PointSize=font_size;
}