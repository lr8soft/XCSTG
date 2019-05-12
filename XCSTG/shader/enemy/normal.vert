#version 330 core
uniform mat4 transform_mat;
in vec4 in_vert;
out vec2 tex_pos;
void main(){
    gl_Position=transform_mat*in_vert;
    vec2 temp_pos=vec2(in_vert);
    if(temp_pos.x<0)
        temp_pos.x=0;
    if(temp_pos.y<0)
        temp_pos.y=0;
    tex_pos=temp_pos;
}