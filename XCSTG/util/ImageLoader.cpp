#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include <iostream>
#include <windows.h>
xc_ogl::ImageLoader::ImageLoader()
{
	texture_type = GL_TEXTURE_2D;
	texture_ptr = nullptr;
	have_release = true;

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
}

xc_ogl::ImageLoader::ImageLoader(GLenum type,GLuint itbo)
{
	texture_type = type;
	texture_ptr = nullptr;
	have_release = true;
	tbo = itbo;
	glBindTexture(texture_type, tbo);
}


xc_ogl::ImageLoader::~ImageLoader()
{
	if (!have_release)
		Release();
}

void xc_ogl::ImageLoader::Release()
{
	if (!have_release) {
		stbi_image_free(texture_ptr);
		have_release = true;
	}		
}

void * xc_ogl::ImageLoader::LoadTextureData(const char * path)
{
	stbi_set_flip_vertically_on_load(true);
	texture_ptr = stbi_load(path, &width, &height, &channel, STBI_rgb_alpha);
	glBindTexture(texture_type, tbo);
	if (texture_ptr) {
		if (channel == 3)//三通道rgb 适用于jpg图像
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//后面一个是RGBA
		else if (channel == 4)//四通道rgba 适用于png图像
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_ptr);//注意，两个都是RGBA
		glGenerateMipmap(texture_type);
		have_release = false;
	}
	else {
		char *str = new char[256];
		sprintf_s(str, 256, "[ERROR]无法加载图像 %s",path);
		MessageBox(NULL, str,"XCSTG ERROR", MB_OKCANCEL|MB_ICONERROR);
		delete[] str;
	}
	glBindTexture(texture_type, 0);//Bind nothing.
	return texture_ptr;
}

GLuint xc_ogl::ImageLoader::GetTBO()
{
	return tbo;
}
