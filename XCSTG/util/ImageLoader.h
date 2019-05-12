#pragma once
#ifndef _image_loader_
#define _image_loader_
#include "stb_image.h"
#include <gl/glcorearb.h>
namespace xc_ogl {
	class ImageLoader
	{
	private:
		GLuint tbo; GLenum texture_type, texture_format;
		int width, height, channel;
		void* texture_ptr;
		bool have_release;
	public:
		ImageLoader();
		ImageLoader(GLenum type,GLenum format,GLuint tbo);
		~ImageLoader();
		void Release();
		void* LoadTextureData(const char* path);
		GLuint GetTBO();
	};
}

#endif 
