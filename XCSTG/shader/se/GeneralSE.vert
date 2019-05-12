#version 330 core
uniform mat4 transform_mat;
in vec4 in_coord;
out vec2 tex_coord;
void main(){
    gl_Position=transform_mat*in_coord;
    vec2 temp_pos=vec2(in_coord);//[-1,1]->[0,1]
    if(temp_pos.x<0)
        temp_pos.x=0;
    if(temp_pos.y<0)
        temp_pos.y=0;
    tex_coord=temp_pos;
}