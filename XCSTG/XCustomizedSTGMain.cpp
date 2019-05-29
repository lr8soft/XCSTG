#include "util/AppFrameWork.h"
#include <mutex>
#include <iostream>
#include <thread>
#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
int exit_code = 0;
std::mutex mutex;
void SetExitType() {
	mutex.lock();
	exit_code++;
	mutex.unlock();
}
int GetExitType() {
	mutex.lock();
	int code = exit_code;
	mutex.unlock();
	return code;
}
void RenderThead() {
	xc_ogl::AppFrameWork app(720, 730, "XCDSTG v0.64");
	app.init();
	app.message_loop();
	SetExitType();
}
int main() {
	std::thread oglThread(RenderThead);
	oglThread.detach();
	while (!GetExitType());
	return 0;
}