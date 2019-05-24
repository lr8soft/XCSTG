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
	accumulateTime += deltaFrame;
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
	accumulateTime += deltaFrame;
}

void XCGameTimer::Clear()
{
	nowFrame = 0.0f;
	deltaFrame = 0.0f;
	lastTime = 0.0f;
	accumulateTime = 0.0;
	FirstRun = true;
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

double XCGameTimer::getAccumlateTime()
{
	return accumulateTime;
}
