#include <iostream>
#include "ShaderReader.h"
#include "AppFrameWork.h"
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include <GL/GLU.h>
#include "stb_image.h"

xc_ogl::AppFrameWork* xc_ogl::AppFrameWork::app_ptr = nullptr;
void xc_ogl::AppFrameWork::finalizer()
{
	glfwDestroyWindow(screen);
	glfwTerminate();
}
void xc_ogl::AppFrameWork::screen_resize(GLFWwindow* screen, int w, int h)
{
	glViewport(0, 0, w, h);
	app_ptr->height = h;
	app_ptr->width = w;
#ifdef _DEBUG
	std::cout << "[INFO]Window resized " << app_ptr->height << "x" << app_ptr->width << std::endl;
#endif
}
void xc_ogl::AppFrameWork::init()
{
	have_init = true;
	glfwInit();
	screen = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(screen);
	glfwSetFramebufferSizeCallback(screen, screen_resize);
	gl3wInit();
	shader_init();
}

void xc_ogl::AppFrameWork::display()
{
	while (!glfwWindowShouldClose(screen)) {
		key_check();
		render();
		glfwSwapBuffers(screen);
		glfwPollEvents();
	}
}
void xc_ogl::AppFrameWork::key_check()
{
}
void xc_ogl::AppFrameWork::shader_init()
{
	bggroup.GroupInit();
	bulletTask.TaskActive();
	enemyTask.TaskActive();
	playerTask.TaskActive();
	taskLoop.SetScreen(screen);
	taskLoop.AddTask(&enemyTask,"A");
	taskLoop.AddTask(&playerTask,"B");
	taskLoop.AddTask(&bulletTask,"C");
}
void xc_ogl::AppFrameWork::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float nowFrame = glfwGetTime();
	bggroup.GroupRender();
	taskLoop.TaskProcess(nowFrame);
	
}


xc_ogl::AppFrameWork::AppFrameWork() :height(720), width(1280), title("OGL Test")
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
	else
		app_ptr = this;
}

xc_ogl::AppFrameWork::AppFrameWork(int w,int h,  const char* t):height(h),width(w),title(t)
{
	if (have_init)
		throw ("Can't create two OpenGL instance.");
	else
		app_ptr = this;
}

void xc_ogl::AppFrameWork::message_loop()
{
	display();
}
