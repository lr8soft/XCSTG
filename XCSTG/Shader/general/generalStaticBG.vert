#version 330 core
layout (location=0) in vec4 vertex_info;//render_pos,texture_pos
out vec2 Tex_coord;
void main(){
    gl_Position =   vec4(vertex_info.xy,    0.0,    1.0);
    Tex_coord   =   vec2(vertex_info.zw);  
}