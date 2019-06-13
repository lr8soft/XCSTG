#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
const int MaxMaterial = 10;
uniform bool isEnable[MaxMaterial];
uniform int useTexType[MaxMaterial];
uniform int texCount;
uniform sampler2D TexHandle0;
uniform sampler2D TexHandle1;
uniform sampler2D TexHandle2;
uniform sampler2D TexHandle3;
uniform sampler2D TexHandle4;
uniform sampler2D TexHandle5;
uniform sampler2D TexHandle6;
uniform sampler2D TexHandle7;
uniform sampler2D TexHandle8;
uniform sampler2D TexHandle9;
vec4 getRenderColor(sampler2D texHnd,vec2 texCoord,int useType)
{
    vec4 returnVec4 = vec4(0.0,0.0,0.0,0.0);
    vec4 samplerValue = texture(texHnd,texCoord);
    float alpha = samplerValue.a;
    switch(useType)
    {
        case 0://diffuse
            returnVec4=0.5 * samplerValue;
            break;
        case 1://specular
            returnVec4=samplerValue;
            break;
        case 2://normal
            returnVec4=samplerValue;
            break;
        case 3://height
            returnVec4=samplerValue;
            break;
        case 4://ambient
            returnVec4=samplerValue;
            break;
        case 5://displacement
            returnVec4=samplerValue;
            break;
        case 6://emissive
            returnVec4=samplerValue;
            break;
        case 7://light
            returnVec4=samplerValue;
            break;
        case 8://opacity
            returnVec4=samplerValue;
            break;
        case 9://reflection
            returnVec4=samplerValue;
            break;
        case 10://shininess
            returnVec4=samplerValue;
            break;
        default:
            returnVec4=samplerValue;
    }
    returnVec4.a = alpha;
    return returnVec4;
}
void main()
{
    vec4 renderColor;
    for(int i=0; i < texCount; i++)
    {
        switch(i)
        {
            case 0:
                renderColor+=getRenderColor(TexHandle0,TexCoords,useTexType[i]);
                 break;
            case 1:
                renderColor+=getRenderColor(TexHandle1,TexCoords,useTexType[i]);
                break;
            case 2:
                renderColor+=getRenderColor(TexHandle2,TexCoords,useTexType[i]);
                break;
            case 3:
                renderColor+=getRenderColor(TexHandle3,TexCoords,useTexType[i]);
                break;
            case 4:
                renderColor+=getRenderColor(TexHandle4,TexCoords,useTexType[i]);
                break;
            case 5:
                renderColor+=getRenderColor(TexHandle5,TexCoords,useTexType[i]);
                break;
            case 6:
                renderColor+=getRenderColor(TexHandle6,TexCoords,useTexType[i]);
                break;
            case 7:
                renderColor+=getRenderColor(TexHandle7,TexCoords,useTexType[i]);
                break;
            case 8:
                renderColor+=getRenderColor(TexHandle8,TexCoords,useTexType[i]);
                break;
            case 9:
                renderColor+=getRenderColor(TexHandle9,TexCoords,useTexType[i]);
                break;
            }
    }
    FragColor= renderColor;
}