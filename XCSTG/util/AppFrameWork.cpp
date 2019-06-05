#include <iostream>
#include "ShaderReader.h"
#include "AppFrameWork.h"
#include "ImageLoader.h"
#include <GL3/gl3w.h>
#include "stb_image.h"
#include <sstream>
#include <al/alut.h>
xc_ogl::AppFrameWork* xc_ogl::AppFrameWork::app_ptr = nullptr;
std::wstring xc_ogl::AppFrameWork::xcstg_version =L"XCSTG测试 v0.67";
void xc_ogl::AppFrameWork::finalizer()
{
	glfwDestroyWindow(screen);
	glfwTerminate();
	alutExit();
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL 3.3 Core Mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式牛 逼
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
	if (glfwGetKey(screen, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		taskLoop.TaskProcessCommand(taskLoop.PROCESS_PAUSE);
	}	
	if (glfwGetKey(screen, GLFW_KEY_Q) == GLFW_PRESS) {
		taskLoop.TaskProcessCommand(taskLoop.PROCESS_RESUME);
	}
}
void xc_ogl::AppFrameWork::shader_init()
{
	taskLoop.SetAbsWidthHeight(1.0f, 1.0f);
	taskLoop.SetWidthHeight(width, height);
	taskLoop.SetScreen(screen);

	taskLoop.AddTask(&bgtask, "0");
	taskLoop.AddTask(&enemyTask,"0");
	taskLoop.AddTask(&playerTask,"0");
	taskLoop.AddTask(&bulletTask, "0");
	taskLoop.AddTask(&bossTask, "0");

	taskLoop.TaskProcessCommand(taskLoop.STAGE_INIT);
	taskLoop.TaskProcessCommand(taskLoop.STAGE_RENDER);

	testFont.FontSetWidthAndHeight(height, width);
	testFont.FontASCIIInit();
}
void xc_ogl::AppFrameWork::render()
{
	gameTimer.Tick();
	taskLoop.TaskProcess(glfwGetTime());
	if (taskLoop.IsProcessing())
	{
		static char fpsShow[64];
		_itoa_s(gameTimer.getFPS(), fpsShow, 10);
		testFont.FontASCIIRender(
			fpsShow,
			0.0f,
			0.96f,
			0.5f,
			glm::vec4(0.3, 0.7f, 0.9f, 1.0f)
		);
		testFont.FontUnicodeDirectRender(
			xcstg_version,
			0.8f,
			0.0f,
			0.3f,
			glm::vec4(0.1, 0.2f, 0.2f, 1.0f)
		);
	}
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
