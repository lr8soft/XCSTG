#version 330 core
uniform mat4 transform_mat;
in vec4 in_coord;
out vec2 tex_pos;
void main(){
    gl_Position=transform_mat*in_coord;
    vec2 temp_tex_pos=vec2(in_coord);
    if(temp_tex_pos.x<0)
        temp_tex_pos.x=0;
    if(temp_tex_pos.y<0)
        temp_tex_pos.y=0;
    tex_pos=temp_tex_pos;
}