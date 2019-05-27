#include <iostream>
#include "ShaderReader.h"
#include "AppFrameWork.h"
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include "stb_image.h"
#include <sstream>
xc_ogl::AppFrameWork* xc_ogl::AppFrameWork::app_ptr = nullptr;
void xc_ogl::AppFrameWork::finalizer()
{
	glfwDestroyWindow(screen);
	glfwTerminate();
	delete XCConfig;
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
	XCConfig = new xc_std::ConfigManager("xcstg.cfg");
	std::stringstream keyUp=XCConfig->get_value("keyup");

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//No resizable.
	//glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);//Auto change size
	screen = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (screen == nullptr) {
		MessageBox(NULL, "无法创建窗口！","ERROR",MB_ICONERROR);
		exit(-1);
	}
	glfwMakeContextCurrent(screen);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(screen, screen_resize);
	gl3wInit();
	shader_init();
}

void xc_ogl::AppFrameWork::display()
{
	while (!glfwWindowShouldClose(screen)) {
		render();
		glfwSwapBuffers(screen);
		glfwPollEvents();
		key_check();
	}
}
void xc_ogl::AppFrameWork::key_check()
{
	if (glfwGetKey(screen, GLFW_KEY_K) == GLFW_PRESS) {
		taskLoop.TaskProcessCommand(taskLoop.CLEAN_BULLET);
	}
	if (glfwGetKey(screen, GLFW_KEY_L) == GLFW_PRESS) {
		taskLoop.TaskProcessCommand(taskLoop.CLEAN_ENEMY);
	}
}
void xc_ogl::AppFrameWork::shader_init()
{
	bggroup.GroupInit();
	taskLoop.SetScreen(screen);
	taskLoop.AddTask(&enemyTask,"0");
	taskLoop.AddTask(&playerTask,"1");
	taskLoop.AddTask(&bulletTask,"2");
	taskLoop.AddTask(&bossTask, "3");
	taskLoop.TaskProcessCommand(taskLoop.STAGE_INIT);
	taskLoop.TaskProcessCommand(taskLoop.STAGE_RENDER);
}
void xc_ogl::AppFrameWork::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	gameTimer.Tick();
	bggroup.GroupRender();
	taskLoop.TaskProcess(gameTimer.getNowFrame());
	
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
