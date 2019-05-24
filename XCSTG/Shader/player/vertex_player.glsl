#version 330 core
uniform mat4 rotate_mat;
in vec4 player_pos;
out vec2 tex_pos;
void main(){
    vec4 temp_pos=rotate_mat*player_pos;
    gl_Position=temp_pos;
    vec2 temp_tex_pos=vec2(player_pos);
    if(temp_tex_pos.x<0)
        temp_tex_pos.x=0;
    if(temp_tex_pos.y<0)
        temp_tex_pos.y=0;
    tex_pos=temp_tex_pos;
}