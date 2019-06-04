#pragma once
#ifndef _XCBACKGROUND_H_
#define _XCBACKGROUND_H_
#include <GL/glcorearb.h>
class XCBackground {
protected:
	bool is_background_render = true;
	virtual void ShaderInit() = 0;
	virtual void TextureInit() = 0;
	virtual void BufferInit() = 0;
public:
	virtual void BackgroundInit() {
		ShaderInit();
		TextureInit();
		BufferInit();
	}
	virtual void BackgroundRender()=0;
	virtual void BackgroundRelease()=0;
	inline void SetBackGroundRender(bool is) 
	{
		is_background_render = is;
	}
	inline bool IsBackGroundRender()
	{
		return is_background_render;
	}
};
#endif