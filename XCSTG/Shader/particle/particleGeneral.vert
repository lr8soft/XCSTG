#version 330 core
uniform mat4 convert_mat;
layout (location=0) in vec4 display_coord;
layout (location=1) in vec3 tex_info;//x,y:tex_coord,z:point size
out vec2 middle_tex_coord;
void main(){
    gl_Position=convert_mat*display_coord;
    gl_PointSize=tex_info.z;
    middle_tex_coord=vec2(tex_info);
}