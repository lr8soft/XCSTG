#version 330 core
uniform sampler2D tex;
uniform int offset;
uniform float gradient_number;
out vec4 render_color;
void main(){
    vec2 tex_coord=gl_PointCoord;
    vec2 calc_coord=gl_PointCoord-vec2(0.5);
    float dist = dot(calc_coord,calc_coord);
    if(dist>=0.25)
         discard;
    if(offset==0){
         vec4 temp_vec4= texture(tex,tex_coord);
         render_color=temp_vec4-vec4(0.0,0.0,0.0,temp_vec4.a*gradient_number);
	}
    else{
        vec4 temp_vec4= texture(tex,tex_coord)*vec4(abs(sin(float(offset)/2.0)),abs(cos(float(offset)/2.0)),abs(sin(float(offset)/2.0)),1.0);
        render_color=temp_vec4-vec4(0.0,0.0,0.0,temp_vec4.a*gradient_number);
    }
    
}