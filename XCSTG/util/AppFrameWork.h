#pragma once
#ifndef _ogl_class_
#define _ogl_class_
#include <GLFW/glfw3.h>
#include "../PlayerRenderGroup.h"
#include "../BackGroundRenderGroup.h"
#include "../EnemyRenderGroup.h"
namespace xc_ogl {
	class AppFrameWork
	{
	private:
		EnemyRenderGroup eygroup;
		BackGroundRenderGroup bggroup;
		PlayerRenderGroup rendergroup;
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
