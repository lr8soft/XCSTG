#version 330 core
uniform sampler2D tex;
uniform int x;
uniform int y;
uniform int m;
uniform int n;
uniform int index;
out vec4 render_tex;
void main()
{
    float temp_x,temp_y;
    switch(index++){
    case 0:
        temp_x=x/m;
        temp_y=y/n;
        break;
    case 1:
        temp_x=x/m;
        temp_y=(y-1)/n;
        break;
    case 2:
        temp_x=(x-1)/m;
        temp_y=(y-1)/n;
        break;
    case 3:
        temp_x=(x-1)/m;
        temp_y=(y-1)/n;
        break;
    case 4:
        temp_x=(x-1)/m;
        temp_y=y/n;
        break;
    case 5:
        temp_x=x/m;
        temp_y=y/n;
        break;
    default:
        discard;
    }
    vec2 temp_coord=vec2(temp_x,temp_y);
    render_tex=texture(tex,temp_coord);
}