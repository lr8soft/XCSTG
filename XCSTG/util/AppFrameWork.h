#pragma once
#ifndef _XCSTG_RENDER_MAIN_
#define _XCSTG_RENDER_MAIN_
#include <GLFW/glfw3.h>
#include "../XCTask/XCTaskLoop.h"
#include "../XCTask/XCPlayerTask.h"
#include "../XCStage/XCBTStage1.h"
#include "../XCStage/XCEYStage1.h"
#include "../rendergroup/BackGroundRenderGroup.h"
#include "../XCStage/XCBossTaskTest.h"
#include "GameTimer.h"
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		XCEYStage1 enemyTask;
		XCPlayerTask playerTask;
		XCBTStage1 bulletTask;
		XCTaskLoop taskLoop;
		TestBossTask bossTask;
		BackGroundRenderGroup bggroup;

		XCGameTimer gameTimer;
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
