#version 330 core
uniform sampler2D tex;
uniform int offset;
void main(){
    vec2 tex_coord=gl_PointCoord;
    vec2 calc_coord=gl_PointCoord-vec2(0.5);
    float dist = dot(calc_coord,calc_coord);
    if(dist>=0.25)
         discard;
    if(offset==0)
         gl_FragColor = texture(tex,tex_coord);
    else
        gl_FragColor = texture(tex,tex_coord)*vec4(abs(sin(offset/2.0)),abs(cos(offset/2.0)),abs(sin(offset)),0.0);
    //+vec4(abs(sin(time)),abs(sin(time/2)),0.1,0.0);
}