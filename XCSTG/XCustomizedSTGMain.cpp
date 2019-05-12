#include "util/AppFrameWork.h"
#include <iostream>
#include <thread>
#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
bool ogl_close = false;
void thread_ogl() {
	xc_ogl::AppFrameWork app(720, 720, "XCDSTG_TEST_2");
	app.init();
	app.message_loop();
	ogl_close = true;
}
void main() {
#ifdef _DEBUG
	std::thread oglThread(thread_ogl);
	oglThread.detach();
	while (!ogl_close);
#else
	thread_ogl();
#endif
}