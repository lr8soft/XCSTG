#include "GameTimer.h"
#include <glfw/glfw3.h>
void XCGameTimer::Tick()
{
	if (!FirstRun) {
		nowFrame = glfwGetTime();
		deltaFrame = nowFrame - lastTime;
		lastTime = nowFrame;
	}
	else {
		nowFrame = glfwGetTime();
		deltaFrame = 0;
		lastTime = nowFrame;
		FirstRun = false;
	}
}

void XCGameTimer::Tick(float update_nowFrame)
{
	if (!FirstRun) {
		nowFrame = update_nowFrame;
		deltaFrame = nowFrame - lastTime;
		lastTime = nowFrame;
	}
	else {
		nowFrame = update_nowFrame;
		deltaFrame = 0;
		lastTime = nowFrame;
		FirstRun = false;
	}
}

float XCGameTimer::getNowFrame()
{
	return nowFrame;
}

float XCGameTimer::getDeltaFrame()
{
	return deltaFrame;
}

float XCGameTimer::getLastFrame()
{
	return lastTime;
}
