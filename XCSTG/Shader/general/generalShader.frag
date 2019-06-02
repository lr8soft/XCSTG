#version 330 core
in vec2 tex_coord;
out vec4 render_tex;
uniform sampler2D tex;
uniform float gradient_number;
void main(){
    vec4 temp_Color=texture(tex,tex_coord);
    render_tex=temp_Color-vec4(0.0,0.0,0.0,temp_Color.a*gradient_number);//RGB-A
}