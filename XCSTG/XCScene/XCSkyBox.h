#pragma once
#ifndef _XCSKYBOX_H_
#define _XCSKYBOX_H_
#include <GL/glcorearb.h>
#include <initializer_list>
class XCSkyBox {
private:
	GLuint vao, vbo, tbo;
public:
	void SkyBoxInit(std::initializer_list<const char*> pathList);
	void SkyBoxRender(float nowFrame);
	void SkyBoxRelease();
};
#endif