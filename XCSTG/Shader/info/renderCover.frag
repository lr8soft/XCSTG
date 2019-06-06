#version 330 core
uniform sampler2D tex;
uniform vec2 render_rate;//vec2(width_rate,height_rate)
in vec2 Tex_coord;
in vec2 check_coord;
out vec4 frag_color;
void main(){
    float render_width=render_rate.x;
    float render_height=render_rate.y;
    if(-render_width<=check_coord.x && render_width>=check_coord.x){
        if(-render_height<=check_coord.y && render_height>check_coord.y){
            discard;
        }
    }
    frag_color  =   texture(tex,Tex_coord);
}