#pragma once
#ifndef _XCBACKGROUND_H_
#define _XCBACKGROUND_H_
#include <GL/glcorearb.h>
#include <iostream>
class XCBackground {
protected:
	float render_abs_width = 1.0f, render_abs_height = 1.0f;
	bool is_background_render = true,have_render_abs_value=false;
	virtual void ShaderInit() = 0;
	virtual void TextureInit() = 0;
	virtual void BufferInit() = 0;
public:
	virtual void BackgroundInit() {
		if (have_render_abs_value) 
		{
			ShaderInit();
			TextureInit();
			BufferInit();
			std::cout << render_abs_width << " " << render_abs_height << std::endl;
		}
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
	void SetAbsWidthAndHeight(float absW,float absH) {
		if (absW != 0 && absH != 0)
		{
			render_abs_width = absW;
			render_abs_height = absH;
			have_render_abs_value = true;
		}
	}
};
#endif