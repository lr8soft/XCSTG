#include "XCSkyBox.h"
#include "../util/ImageLoader.h"
#include <GL3/gl3w.h>
#include <vector>
using namespace xc_ogl;
void XCSkyBox::SkyBoxInit(std::initializer_list<const char*> pathList)
{
	ImageLoader texLoader;
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &tbo);
	int width = 0, height = 0, channel = 3;
	std::vector<void*> path;
	int i = 0;
	for (auto iter = pathList.begin(); iter != pathList.end(); iter++, i++) {
		path[i] = texLoader.getTexturePointer(*iter,width,height,channel);
	}
	glTextureStorage2D(tbo, 0, GL_RGBA8, width, height);
	for (int j = 0; i < i;j++) {
		glTextureSubImage3D(tbo, 0, 0, 0, j, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, &path[j]);
	}
	glGenerateTextureMipmap(tbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

}

void XCSkyBox::SkyBoxRender(float nowFrame)
{
	
}

void XCSkyBox::SkyBoxRelease()
{
}
