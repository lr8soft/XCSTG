#version 330 core
in vec2 tex_coord;
out vec4 render_tex;
uniform sampler2D tex;
void main(){
    render_tex=texture(tex,tex_coord);
}