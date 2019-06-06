#version 330 core
uniform mat4 rotate_mat;
layout (location=0) in vec4 player_pos;
out vec2 tex_pos;
void main(){
    gl_Position=rotate_mat*vec4(player_pos.xy,0.0,1.0);
    tex_pos=vec2(player_pos.zw);
}