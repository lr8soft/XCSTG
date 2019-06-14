#version 330 core
layout (location = 1) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTangent;
layout (location = 5) in vec2 aBitangent;
out vec2 TexCoords;
out vec4 RenderCoords;
uniform mat4 mvp_mat;
void main()
{  
    vec4 tempCoords = mvp_mat * vec4(aPosition, 1.0);
    gl_Position = tempCoords;
    RenderCoords = tempCoords;
    TexCoords = aTexCoords;  
}