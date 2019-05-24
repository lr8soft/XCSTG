#version 330 core
in vec4 in_vertex;
out vec2 tex_pos;
void main(){
    gl_Position=in_vertex;
    vec2 temp_pos=vec2(in_vertex);
    if(temp_pos.x<0)
        temp_pos.x=0;
    if(temp_pos.y<0)
        temp_pos.y=0;
    tex_pos=temp_pos;
}