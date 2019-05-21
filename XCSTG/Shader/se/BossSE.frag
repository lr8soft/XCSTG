#version 330 core
uniform float time;
out vec4 render_color;
void main(){
    render_color=vec4(abs(sin(time)),abs(cos(time)),1.0,0.5);//texture(tex,tex_coord);
}