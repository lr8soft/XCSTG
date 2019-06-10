#version 330 core
layout (location = 1) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTangent;
layout (location = 5) in vec2 aBitangent;
out vec2 TexCoords;
uniform mat4 mvp_mat;
void main()
{  
    gl_Position = mvp_mat * vec4(aPosition, 1.0);
    TexCoords = aTexCoords;  
}