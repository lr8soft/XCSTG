#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
const int MaxMaterial = 10;
struct XCTexMaterial
{
    bool isEnable[MaxMaterial];
    int useTexType[MaxMaterial];
    int texCount;
};
uniform sampler2DArray textureGroup;
uniform XCTexMaterial materialInfo;
void main()
{
    vec3 blendColor=vec3(1.0,1.0,1.0);
    float alpha=0.0;
    for(int i=0;i<materialInfo.texCount;i++){
        if(materialInfo.isEnable[i]==false)
            continue;
        vec4 texSampler=texture(textureGroup,vec3(TexCoords,i));
        blendColor*=texSampler.rgb;
        alpha+=texSampler.a;
    }
    FragColor=vec4(blendColor,alpha);
}