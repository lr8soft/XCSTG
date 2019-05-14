#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include <iostream>
#include <windows.h>
xc_ogl::ImageLoader::ImageLoader()
{
	stbi_set_flip_vertically_on_load(true);//������s
	texture_type = GL_TEXTURE_2D;
	texture_format = GL_RGBA;
	texture_ptr = nullptr;
	have_release = true;

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
}

xc_ogl::ImageLoader::ImageLoader(GLenum type, GLenum format,GLuint itbo)
{
	ImageLoader();
	texture_type = type;
	texture_format = format;
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
	texture_ptr = stbi_load(path, &width, &height, &channel, 4);
	glBindTexture(texture_type, tbo);
	if (texture_ptr) {
		glTexImage2D(texture_type, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, texture_ptr);
		glGenerateMipmap(texture_type);
		have_release = false;
	}
	else {
		char *str = new char[256];
		sprintf_s(str, 256, "[ERROR]Failed to load %s",path);
		MessageBox(NULL, str,"XCSTG ERROR", MB_OKCANCEL);
		delete[] str;
	}
	glBindTexture(texture_type, 0);//Bind nothing.
	return texture_ptr;
}

GLuint xc_ogl::ImageLoader::GetTBO()
{
	return tbo;
}
