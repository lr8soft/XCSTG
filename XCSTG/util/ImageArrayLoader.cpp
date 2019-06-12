#include "ImageArrayLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <GL3/gl3w.h>
#include <iostream>
#include <windows.h>
xc_ogl::ImageArrayLoader::ImageArrayLoader()
{
	
	glGenTextures(1, &tbo);
}

void xc_ogl::ImageArrayLoader::loadTextureFromFile(int allCount,const char * path)
{
	glGetError();
	stbi_set_flip_vertically_on_load(true);
	void* texture_ptr = stbi_load(path, &width, &height, &channel, STBI_rgb_alpha);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tbo);
	if (texture_ptr) {
		if (channel == 3) {
			if (0 == texCount)
			{
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB8, width, height, allCount, 0, GL_RGBA, GL_UNSIGNED_BYTE,NULL);
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, texCount++,
					width, height,
					1,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					texture_ptr);
			}
			else {
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, texCount++,
					width, height,
					1,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					texture_ptr);
			}
		}
		else if (channel == 4) {
			if (0 == texCount)
			{
				glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, allCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, texCount++,
					width, height,
					1,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture_ptr);
			}
			else {
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
					0,
					0, 0, texCount++,
					width, height,
					1,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture_ptr);
			}
		}
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	}
	else {
		char *str = new char[256];
		sprintf_s(str, 256, "[ERROR]Œﬁ∑®º”‘ÿÕºœÒ %s", path);
		MessageBox(NULL, str, "XCSTG ERROR", MB_OKCANCEL | MB_ICONERROR);
		delete[] str;
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);//Bind nothing.
	stbi_image_free(texture_ptr);
	
}

GLuint xc_ogl::ImageArrayLoader::getTextureBufferObjectHandle()
{
	return tbo;
}
