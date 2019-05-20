#include "util/AppFrameWork.h"
#include <iostream>
#include <thread>
#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
void main() {
	xc_ogl::AppFrameWork app(720, 730, "XCDSTG_TEST_2");
	app.init();
	app.message_loop();
}