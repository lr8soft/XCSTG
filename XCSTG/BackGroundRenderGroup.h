#pragma once
#ifndef _BGRender_GROUP_
#define _BGRender_GROUP_
#include <gl/glcorearb.h>
#include <GLFW/glfw3.h>
class BackGroundRenderGroup
{
private:
	GLuint vao, vbo, tbo[3],use_tbo;
	GLuint program;
	bool RenderBG=true;
	void BufferLoader();
	void TextureLoader();
	void ShaderLoader();
	void BackGroundTexSet(GLuint tbo);
public:
	BackGroundRenderGroup()=default;
	~BackGroundRenderGroup()=default;
	void GroupInit();
	void GroupRender();
	void SetRender(bool dorender);
	void GroupKeyCheck(GLFWwindow* screen);
};

#endif