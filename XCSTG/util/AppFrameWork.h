#pragma once
#ifndef _XCSTG_RENDER_MAIN_
#define _XCSTG_RENDER_MAIN_
#include <GLFW/glfw3.h>
#include "../XCTask/XCTaskLoop.h"
#include "../XCTask/XCEnemyTask.h"
#include "../XCTask/XCPlayerTask.h"
#include "../XCTask/XCBulletTask.h"
#include "../rendergroup/BackGroundRenderGroup.h"
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		XCEnemyTask enemyTask;
		XCPlayerTask playerTask;
		XCBulletTask bulletTask;
		XCTaskLoop taskLoop;
		BackGroundRenderGroup bggroup;

		static AppFrameWork* app_ptr;
		const char* title;
		int width, height;
		bool have_init = false;
		GLFWwindow* screen;
		static void screen_resize(GLFWwindow*,int,int);
		void display();
		void key_check();
		void render();
		void shader_init();
	public:
		AppFrameWork();
		AppFrameWork(int width,int height,const char* title);
		~AppFrameWork()=default;
		void finalizer();
		void init();
		void message_loop();
	};
}

#endif
