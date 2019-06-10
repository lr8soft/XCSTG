#pragma once
#ifndef _XCSTG_RENDER_MAIN_
#define _XCSTG_RENDER_MAIN_
#include <GLFW/glfw3.h>
#include "../XCTask/XCTaskLoop.h"
#include "../XCTask/XCPlayerTask.h"
#include "../XCStage/XCBTStage1.h"
#include "../XCStage/XCEYStage1.h"
#include "../XCStage/XCBossTaskTest.h"
#include "../XCFont/XCFont.h"
#include "../XCStage/XCTestBG.h"
#include "../XCModel/XCModel.h"
#include "GameTimer.h"
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		XCModel *modeltest;
		XCEYStage1 enemyTask;
		XCTestBG bgtask;
		XCPlayerTask playerTask;
		XCBTStage1 bulletTask;
		XCTaskLoop taskLoop;
		TestBossTask bossTask;

		XCFont testFont;
		XCGameTimer gameTimer;
		static AppFrameWork* app_ptr;
		static std::wstring xcstg_version;
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
