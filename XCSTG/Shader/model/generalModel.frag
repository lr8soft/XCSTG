#version 330 core
in vec2 TexCoords;
in vec4 RenderCoords;
out vec4 FragColor;
const int MaxMaterial = 10;
const bool useNormalAndHeight = false;
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
vec4 getRenderColor(sampler2D texHnd,vec2 texCoord,int useType,out bool isNormalTex)
{
    vec4 returnVec4 = vec4(0.0,0.0,0.0,0.0);
    vec4 samplerValue = texture(texHnd,texCoord);
    float alpha = samplerValue.a;

    vec3 normalVec3 = vec3(0.0,0.0,0.0);
    switch(useType)
    {
        case 0://diffuse
            returnVec4=0.5 * samplerValue;
            break;
        case 1://specular
            returnVec4=samplerValue;
            break;
        case 2://normal
            if(useNormalAndHeight)
            {
                isNormalTex=true;
                normalVec3=vec3(samplerValue);
            }
            break;
        case 3://height
            if(useNormalAndHeight)
            {
                isNormalTex=true;
                float h21 = textureOffset(texHnd,texCoord,ivec2(1,0)).r;
                float h01 = textureOffset(texHnd,texCoord,ivec2(-1,0)).r;
                float h10 = textureOffset(texHnd,texCoord,ivec2(0,-1)).r;
                float h12 = textureOffset(texHnd,texCoord,ivec2(0,1)).r;
                vec3 vr = normalize(vec3(2.0f,0.0f,h21 - h01));
                vec3 vt = normalize(vec3(0.0f,2.0f,h12 - h10));
                normalVec3 = normalize(cross(vr,vt));
            }

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
    if(!isNormalTex){
        returnVec4.a = alpha;
        return returnVec4;
    }else{
        if(useNormalAndHeight)
        {                                /*light position*/
            vec3 lightDir = normalize(vec3(80.0,80.0,0.0) - vec3(RenderCoords));
            float diff = max(dot(normalVec3, lightDir), 0.0);
            vec3 diffuse = diff * vec3(0.0,0.0,0.0);/*light color*/
            return vec4(diffuse,1.0);            
        }else{
            return samplerValue;
        }

    }
}
void main()
{
    vec4 renderColor,returnColor;
    bool isNormalTex = false, haveUnrenderVec3 =false;
    vec4 tempColor;
    for(int i=0; i < texCount; i++)
    {
        if(haveUnrenderVec3){
            renderColor += vec4(tempColor.rgb,renderColor.a) * renderColor;
            haveUnrenderVec3=false;
        }
        switch(i)
        {
            case 0:
                returnColor=getRenderColor(TexHandle0,TexCoords,useTexType[i],isNormalTex);
                 break;
            case 1:
                returnColor=getRenderColor(TexHandle1,TexCoords,useTexType[i],isNormalTex);
                break;
            case 2:
                returnColor=getRenderColor(TexHandle2,TexCoords,useTexType[i],isNormalTex);
                break;
            case 3:
                returnColor=getRenderColor(TexHandle3,TexCoords,useTexType[i],isNormalTex);
                break;
            case 4:
                returnColor=getRenderColor(TexHandle4,TexCoords,useTexType[i],isNormalTex);
                break;
            case 5:
                returnColor=getRenderColor(TexHandle5,TexCoords,useTexType[i],isNormalTex);
                break;
            case 6:
                returnColor=getRenderColor(TexHandle6,TexCoords,useTexType[i],isNormalTex);
                break;
            case 7:
                returnColor=getRenderColor(TexHandle7,TexCoords,useTexType[i],isNormalTex);
                break;
            case 8:
                returnColor=getRenderColor(TexHandle8,TexCoords,useTexType[i],isNormalTex);
                break;
            case 9:
                returnColor=getRenderColor(TexHandle9,TexCoords,useTexType[i],isNormalTex);
                break;
            }
            if(isNormalTex)
            {
                if(useNormalAndHeight)
                {
                    if(i!=0){
                        renderColor += vec4(returnColor.rgb,renderColor.a) * renderColor;
                        isNormalTex = false;
                    }else{
                        tempColor = returnColor;
                        haveUnrenderVec3=true;
                    }
                }else{
                    renderColor += returnColor;
                }
                
            }else{
                renderColor += returnColor;
            }
    }
    FragColor= renderColor;
}