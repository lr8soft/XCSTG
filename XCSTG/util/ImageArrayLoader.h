#pragma once
#ifndef _IMAGEARRAY_LOADER_H_
#define _IMAGEARRAY_LOADER_H_
#include "stb_image.h"
#include <gl/glcorearb.h>
namespace xc_ogl {
	class ImageArrayLoader {
	private:
		GLuint tbo = -1;
		int width, height, channel, texIndex = 0;
		int first_w, first_h;
		bool have_init=false;
	public:
		ImageArrayLoader();
		void loadTextureFromFile(int allCount, const char* path);
		GLuint getTextureBufferObjectHandle();
	};
}
#endif