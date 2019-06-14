#pragma once
#ifndef _XCBACKGROUNDSTATIC_H_
#define _XCBACKGROUNDSTATIC_H_
#include "XCBackground.h"
#include <string>
class XCBackgroundStatic:public XCBackground {
protected:
	GLuint vao=-1, vbo=-1, tbo=-1, program=-1;
	std::string texturePath;
	virtual void ShaderInit();
	virtual void TextureInit();
	virtual void BufferInit();
public:
	XCBackgroundStatic();
	void LoadBackGround(std::string tex_path);
	void LoadBackGround(GLuint textureHandle);
	virtual void BackgroundRender(float nowFrame);
	virtual void BackgroundRelease();
};
#endif